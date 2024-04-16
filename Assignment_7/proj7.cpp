#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Function to convert a string to lowercase
string toLowerCase(const string& input) {
    string lower = input;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

int main() {
    unordered_map<char, int> charFrequency;
    unordered_map<string, int> wordFrequency;
    unordered_map<string, int> numberFrequency;

    char c;
    string word, number;
    
    string fileName;
    cout << "Enter the name of the file to read: ";
    cin >> fileName;

    // Open the file
    ifstream inputFile(fileName);
    if (!inputFile) {
        cout << "Error: Could not open the file." << endl;
        return 1;
    }

    // Read input from the file until end of file is reached
    while (inputFile.get(c)) {
        if (isalpha(c)) {
            word += c;
        } else if (isdigit(c)) {
            number += c;
        } else if (!word.empty()) {
            wordFrequency[toLowerCase(word)]++;
            word.clear();
        } else if (!number.empty()) {
            numberFrequency[number]++;
            number.clear();
        }

        if (isprint(c) || c == ' ' || c == '\t' || c == '\n') {
            charFrequency[c]++;
        }
    }

    // Close the file
    inputFile.close();

    // Store the results in vectors of pairs for easier sorting
    vector<pair<int, char>> charFrequencyVec;
    for (const auto& entry : charFrequency) {
        charFrequencyVec.push_back({ entry.second, entry.first });
    }

    vector<pair<int, string>> wordFrequencyVec;
    for (const auto& entry : wordFrequency) {
        wordFrequencyVec.push_back({ entry.second, entry.first });
    }

    vector<pair<int, string>> numberFrequencyVec;
    for (const auto& entry : numberFrequency) {
        numberFrequencyVec.push_back({ entry.second, entry.first });
    }

    // Sort the vectors in descending order of frequencies
    sort(charFrequencyVec.rbegin(), charFrequencyVec.rend());
    sort(wordFrequencyVec.rbegin(), wordFrequencyVec.rend());
    sort(numberFrequencyVec.rbegin(), numberFrequencyVec.rend());

    // Output the top ten most used characters
    cout << "Top Ten Characters:" << endl;
    for (int i = 0; i < min(10, static_cast<int>(charFrequencyVec.size())); ++i) {
        char character = charFrequencyVec[i].second;
        if (character == '\t') {
            cout << "\\t";
        } else if (character == '\n') {
            cout << "\\n";
        } else {
            cout << character;
        }
        cout << ": " << charFrequencyVec[i].first << endl;
    }


    // Output the top ten most used numbers
    cout << "Top Ten Numbers:" << endl;
    for (int i = 0; i < min(10, static_cast<int>(numberFrequencyVec.size())); ++i) {
        cout << numberFrequencyVec[i].second << ": " << numberFrequencyVec[i].first << endl;
    }

    // Output the top ten most used words
    cout << "Top Ten Words:" << endl;
    for (int i = 0; i < min(10, static_cast<int>(wordFrequencyVec.size())); ++i) {
        cout << wordFrequencyVec[i].second << ": " << wordFrequencyVec[i].first << endl;
    }

    return 0;
}