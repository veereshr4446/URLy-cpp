#include <iostream>
#include <string>
#include <map>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <ctime>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

// ---------- URL SHORTENER LOGIC ----------
map<string, string> url_database;

string generate_short_code() {
    string characters = "abcdefghijklmnopqrstuvwxyz0123456789";
    string short_code = "";
    for (int i = 0; i < 6; i++) {
        int random_index = rand() % characters.length();
        short_code += characters[random_index];
    }
    return short_code;
}

string shorten_url(const string& long_url) {
    string short_code;
    do {
        short_code = generate_short_code();
    } while (url_database.find(short_code) != url_database.end());
    
    url_database[short_code] = long_url;
    return short_code;
}

// ---------- HTTP SERVER LOGIC ----------
string http_response(const string& content) {
    string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: application/json\r\n";
    response += "Content-Length: " + to_string(content.length()) + "\r\n";
    response += "Connection: close\r\n";
    response += "\r\n";
    response += content;
    return response;
}

int main() {
    srand(time(0));
    
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        cout << "Socket creation failed!" << endl;
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        cout << "Bind failed! Port 8080 might be in use." << endl;
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    listen(server_socket, 5);

    cout << "========================================" << endl;
    cout << "🚀 URL SHORTENER API SERVER" << endl;
    cout << "📡 Running on http://localhost:8080" << endl;
    cout << "✂️ Try: http://localhost:8080/shorten?url=google.com" << endl;
    cout << "🏓 Test: http://localhost:8080/ping" << endl;
    cout << "========================================" << endl;
    cout << "Press Ctrl+C to stop." << endl;

    while (true) {
        SOCKET client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == INVALID_SOCKET) continue;

        char buffer[4096] = {0};
        recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        string request(buffer);

        string response;

        if (request.find("/ping") != string::npos) {
            // CHANGE YOUR NAME HERE!
            response = http_response("{\"status\":\"alive\",\"message\":\"Viresh's URL Shortener is running!\"}");
        }
        else if (request.find("/shorten?url=") != string::npos) {
            size_t url_start = request.find("/shorten?url=") + 12;
            size_t url_end = request.find(" ", url_start);
            string long_url = request.substr(url_start, url_end - url_start);
            
            string short_code = shorten_url(long_url);
            string json = "{\"short_code\":\"" + short_code + "\",\"long_url\":\"" + long_url + "\"}";
            response = http_response(json);
            
            cout << "✂️ Shortened: " << long_url << " → " << short_code << endl;
        }
        else {
            response = http_response("{\"error\":\"Not found. Try /ping or /shorten?url=...\"}");
        }

        send(client_socket, response.c_str(), response.length(), 0);
        closesocket(client_socket);
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}