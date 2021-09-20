//
// Created by Jacob on 9/19/2021.
//

#include <vector>
#include "hash.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <regex>

using namespace std;


// Class to House Functions of Spell Checker
class spellChecker{
private:
    hashTable dictionary = hashTable(10000);

public:
    unsigned long readDic(string fileName);
    unsigned long spellCheck(string inputFile, string outputFile);
    string makeValidWord(string word); //puts all characters in lower case; if word is invalid (too long or contains a non-alphanumeric, returns an empty string)
    bool alpha(string word); //if string is only chars returns true
    string makeLower(string word); //coverts a string to lower case
    int wordTooLong = 0; //used for debugging
    int badChar = 0; //used for debugging
    auto resplit(const std::string & s, std::string rgx_str = "[^a-zA-Z0-9-']{1,24}");

};

auto spellChecker::resplit(const string &s, std::string rgx_str) {
    std::vector<std::string> elems;

    std::regex rgx (rgx_str);

    std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
    std::sregex_token_iterator end;

    while (iter != end)  {
        elems.push_back(*iter);
        ++iter;
    }
    return elems;
}

unsigned long spellChecker::readDic(string fileName) {

    clock_t c_start = clock();
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        c_start = clock();
        while (getline(file, line)) {
            string word = ("%s", line.c_str());
            string updatedWord = this->makeValidWord(word);
            if (updatedWord.length() != 0){
                dictionary.insert(updatedWord);
            }
        }
        file.close();
    }
    clock_t c_end = clock();
    return c_end-c_start;
}

string spellChecker::makeValidWord(string word = "hello") {

    if (word.length() > 20){
        wordTooLong++;
        return "";
    }

    for (auto it = word.begin(); it != word.end(); ++it) {
        if(!isalnum(*it) && *it !='-' && *it != '\''){ //if there is a separator in the word - ignore
            this->badChar++;
            return "";

        }else{
                *it = ::tolower(*it); //does this here to avoid cycling again through
        }
    };
        return word;

}

unsigned long spellChecker::spellCheck(string inputFile, string outputFile) {
    clock_t c_start = clock();
    ifstream file(inputFile);
    ofstream outFile;
    outFile.open(outputFile);
    int linenum = 1;
    if (file.is_open()) {
        string line;
        c_start = clock();
        while (getline(file, line)) {
            string line1 = line.c_str();
            vector<string> words = resplit(line1);
            for (auto & word : words) {
                if(alpha(word)) {
                    if(word.length() > 20){
                        outFile << "Long word at line " << linenum << ", starts: " << this->makeLower(word.substr(0,20)) << '\n';
                    }else{
                        string validate = this->makeValidWord(word);
                        bool cont = dictionary.contains(validate);
                        if(!cont && validate.length() > 0)
                            outFile << "Unknown word at line " << linenum <<": " << validate << '\n';
                    }
                }
            }
            linenum++;
        }

    }
    clock_t c_end = clock();
    file.close();
    return c_end-c_start;
}

string spellChecker::makeLower(string word) {
    std::for_each(word.begin(), word.end(), [](char & c) {
        c = ::tolower(c);
    });
    return word;
}

bool spellChecker::alpha(string word) {
    int i = 0;
    while (word[i])
    {
        if (!isalpha(word[i]) && word[i] != '-' && word[i] != '\''){return false;}
        i++;
    }
    return true;
}




int main () {

    spellChecker spell = spellChecker();
    cout << "Enter name of dictionary: ";
    string dict_file;
    cin >> dict_file;
    unsigned long time = spell.readDic(dict_file) ;
    cout << "Total time (in seconds) to load dictionary: " << (time * 1000.00 / (CLOCKS_PER_SEC * 1000.00)) << '\n';

    string inFile;
    string outFile;
    cout << "Enter name of input file: ";
    cin >> inFile;
    cout << "Enter name of output file: ";
    cin >> outFile;

    unsigned long time1 = spell.spellCheck(inFile, outFile);
    cout << "Total time (in seconds) to check document: " << (time1 * 1000.000 / (CLOCKS_PER_SEC * 1000.00));



    return 0;
}
