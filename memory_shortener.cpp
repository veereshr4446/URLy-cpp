/*#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// This is our "Database" (just RAM for now)
unordered_map<string, string> url_database;

// Function to "shorten" a URL (super basic version)
string shorten_url(const string& long_url) {
    // We just use the length of the URL as a "fake" short code for now
    string short_code = "code_" + to_string(long_url.length());
    url_database[short_code] = long_url;
    return short_code;
}

int main() {
    // 1. User gives us a long URL
    string long_url = "https://www.google.com/maps/place/Ballari";
    
    // 2. We shorten it
    string short_code = shorten_url(long_url);
    
    // 3. We show the result
    cout << "🔗 Long URL: " << long_url << endl;
    cout << "✂️ Short Code: " << short_code << endl;
    cout << "💾 Stored in memory!" << endl;
    
    // 4. We retrieve it (just to prove it works)
    cout << "🔍 Retrieved: " << url_database[short_code] << endl;
    
    return 0;
}*/