#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

unordered_map<string, string> url_database;

string generate_short_code() {
    string characters = "abcdefghijklmnopqrstuvwxyz0123456789";
    string short_code = "";
    for (int i = 0; i < 6; i++) {
        int random_index = rand() % characters.length();
        short_code += characters[random_index];
    }
    return short_code;
}

void load_from_file() {
    ifstream file("urls.txt");
    string short_code, long_url;
    while (file >> short_code >> long_url) {
        url_database[short_code] = long_url;
    }
    file.close();
}

void save_to_file(const string& short_code, const string& long_url) {
    ofstream file("urls.txt", ios::app);
    file << short_code << " " << long_url << endl;
    file.close();
}

string shorten_url(const string& long_url) {
    string short_code;
    do {
        short_code = generate_short_code();
    } while (url_database.find(short_code) != url_database.end());
    
    url_database[short_code] = long_url;
    save_to_file(short_code, long_url);
    return short_code;
}

int main() {
    srand(time(0));
    load_from_file();
    
    cout << "📂 Loaded " << url_database.size() << " existing URLs!" << endl;
    
    string long_url;
    cout << "Enter URL to shorten: ";
    
    // FIX: This reads the ENTIRE line, even if it's super long
    getline(cin, long_url);
    
    // If the user accidentally pressed enter, ask again
    if (long_url.empty()) {
        cout << "Please enter a URL: ";
        getline(cin, long_url);
    }
    
    string short_code = shorten_url(long_url);
    
    cout << "\n========================================" << endl;
    cout << "🔗 Long URL: " << long_url << endl;
    cout << "✂️ Short Code: " << short_code << endl;
    cout << "💾 Saved to file: urls.txt" << endl;
    cout << "========================================" << endl;
    
    // Wait for user to press Enter before closing
    cout << "\nPress Enter to exit...";
    cin.get();
    
    return 0;
}