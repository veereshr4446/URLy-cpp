#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>  // For file operations

using namespace std;

unordered_map<string, string> url_database;

// Load from file when program starts
void load_from_file() {
    ifstream file("urls.txt");
    string short_code, long_url;
    while (file >> short_code >> long_url) {
        url_database[short_code] = long_url;
    }
    file.close();
}

// Save to file when we add a new URL
void save_to_file(const string& short_code, const string& long_url) {
    ofstream file("urls.txt", ios::app);  // Append mode
    file << short_code << " " << long_url << endl;
    file.close();
}

string shorten_url(const string& long_url) {
    string short_code = "code_" + to_string(long_url.length());
    url_database[short_code] = long_url;
    save_to_file(short_code, long_url);  // Save to file!
    return short_code;
}

int main() {
    load_from_file();  // Load existing URLs
    
    cout << "📂 Loaded " << url_database.size() << " existing URLs from file!" << endl;
    
    string long_url = "https://www.google/map.com";
    string short_code = shorten_url(long_url);
    
    cout << "🔗 Long URL: " << long_url << endl;
    cout << "✂️ Short Code: " << short_code << endl;
    cout << "💾 Saved to file: urls.txt" << endl;
    
    // Show all stored URLs
    cout << "\n📋 All stored URLs:" << endl;
    for (const auto& pair : url_database) {
        cout << "  " << pair.first << " → " << pair.second << endl;
    }
    
    return 0;
}