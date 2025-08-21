// Gran cantidad de este código fue generado por chatGPT
// Yo lo adapté para simplificarlo para la clase

#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

// Linear search spell checker (very inneficient)
vector<string> spellCheckLinear( const vector<string>& text, const vector<string>& dictionary)  {
    vector<string> misspelled;

    // For each word in the text, let's try to find it in the dictionary vector.
    for (const string& word : text) {
        bool found = false;

        // Unfortunately searching the vector requires us to use linear search, which
        // has complexity O(n) 😢
        for (const string& dictWord : dictionary) {
            if (word == dictWord) {
                found = true;
                break;
            }
        }
        if (!found) {
            misspelled.push_back(word);
        }
    }
    return misspelled;
}

// Spell checker using unordered_set (hash table)
vector<string> spellCheckHash(const vector<string>& text, const vector<string>& dictionary)  {

    // Creates the unordered set and inserts all the words
    unordered_set<string> dictSet(dictionary.begin(), dictionary.end());
    vector<string> misspelled;

    // For each word in the text, let's try to find it in the unordered set.
    for (const string& word : text) {
        // Searching in an unordered set has complexity O(1) 🎉
        if (dictSet.find(word) == dictSet.end()) {
            misspelled.push_back(word);
        }
    }
    return misspelled;
}

int main() {
    vector<string> dictionary;
    vector<string> text;

    ifstream inFile("words02.txt");
    ifstream inFileText("ulysses01.txt");
    
    string tmp;

    if (!inFile) cout << "could nt find file\n";
    while(inFile >> tmp ) dictionary.push_back(tmp);
    while(inFileText >> tmp ) text.push_back(tmp);

    cout << "The file with the correctly spell words contains:" << dictionary.size() << " words.\n" ;
    cout << "The text to be spell checked contains:" << text.size() << " words\n";
    
    auto start = chrono::steady_clock::now();  
    auto miss1 = spellCheckLinear(text, dictionary);
    auto end = chrono::steady_clock::now();  

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "\nusing linear search: " << duration << "\n";
    
    start = chrono::steady_clock::now();  
    auto miss2 = spellCheckHash(text, dictionary);
    end = chrono::steady_clock::now(); 
    duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "\nusing Hash: " << duration << "\n";

    return 0;
}
