//
// Created by Jacob on 9/19/2021.
//

#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <regex>
#include <unistd.h>

using namespace std;

std::string gen_random(const int len) {

    std::string tmp_s;
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz-'"
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz-'""0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz-'""0123456789"
            "ABCDEFGHIJKLMNOP__QRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz-'""0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklm$nopqrstuvwxyz-'";


    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];


    return tmp_s;

}

std::string gen_random1(const int len) {

    std::string tmp_s;
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTU VWXYZ"
            "abcd  efgh ijklmnopqrst uvwxyz-'"
            "0123456789"
            "ABCDEFGH IJKLMNOPQRS TUVWXYZ"
            "abcdefghi jklmnopqr stuvwxyz-'""0123456789"
            "ABCDEFGHIJKLMNOPQ RSTUVWXYZ"
            "abcdefghijklmno$ pqrstuvwxyz-'""0123456789"
            "ABCD@EFGHIJKLMNOPQRSTUVWXYZ"
            "abcde   fghijklmnopqrstuvwxyz-'""0123456789"
            "ABCDEFGHIJ KLMNO^PQRSTUVWXYZ"
            "abcdefqwertyuioasdfghjkl.__ghijklm$nopqrstuvwxyz-'";


    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];


    return tmp_s;

}

auto resplit(const std::string & s, std::string rgx_str = "[^\\w-']{1,24}") {


    std::vector<std::string> elems;

    std::regex rgx (rgx_str);

    std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
    std::sregex_token_iterator end;

    while (iter != end)  {
        //std::cout << "S43:" << *iter << std::endl;
        elems.push_back(*iter);
        ++iter;
    }

    return elems;

}


int main() {

    string s = "This is a sample sentence !with- []s.";
    vector<string> v22 = resplit(s);

    for (const auto & e: v22) {
        cout <<"Token:" << e << endl;
    }

    /*
    ofstream outFile;
    outFile.open("dictionary.txt");
    int i = 0;
    while (i < 1000000) {
        outFile << gen_random(rand() % 25 + 1) << '\n';
        i++;
    }
    outFile.close();


    ofstream outFile2;
    outFile2.open("document.txt");
    int j = 0;
    while (j < 10000) {
        outFile2 << gen_random1(rand() % 50 + 1) << '\n';
        j++;
    }
    outFile2.close();*/

}