#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


const int PRIME = 101; // Choose a large prime number


int hash_func(const string& str) {
    int hash_value = 0;
    const int d = 256; // Number of characters in the input alphabet
    for (char c : str) {
        hash_value = (d * hash_value + c) % PRIME;
    }
    return hash_value;
}


int rolling_hash(const string& text, int start, int end) {
    int hash_value = 0;
    const int d = 256;
    const int p = 1; // Power of the base (can be chosen as 1 here)
    for (int i = start; i < end; ++i) {
        hash_value = (d * hash_value + text[i]) % PRIME;
    }
    return hash_value;
}


void printHighlightedLine(const string& line, int startIndex, int patternLength) {
    cout << "Line: " << line.substr(0, startIndex)
         << "\033[1;31m" << line.substr(startIndex, patternLength) << "\033[0m"
         << line.substr(startIndex + patternLength) << " <--- Found here!\n" << endl;
}


bool findAndHighlightPattern(const string& pattern, const string& text) {
    int pattern_length = pattern.length();
    int pattern_hash = hash_func(pattern);
    bool found = false;


    istringstream textStream(text);
    string line;
    int lineIndex = 0;


    while (getline(textStream, line)) {
        int text_length = line.length();


        for (int i = 0; i <= text_length - pattern_length; i++) {
            int text_hash = rolling_hash(line, i, i + pattern_length);


            if (text_hash == pattern_hash && line.compare(i, pattern_length, pattern) == 0) {
                printHighlightedLine(line, i, pattern_length);
                found = true;
            }
        }


        lineIndex++;
    }


    return found;
}


int main() {
    string filename, text, pattern;


    cout << "Enter the filename: ";
    cin >> filename;


    ifstream inputFile(filename);


    if (!inputFile.is_open()) {
        cout << "Error opening the file." << endl;
        return 1;
    }


    // Read the entire content of the file into the 'text' variable
    stringstream buffer;
    buffer << inputFile.rdbuf();
    text = buffer.str();


    inputFile.close();


    cout << "Enter the pattern: ";
    cin >> pattern;


    if (!findAndHighlightPattern(pattern, text)) {
        cout << "Pattern not found" << endl;
    }


    return 0;
}
