#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>    
#include <iostream>     // std::cout, std::endl
#include <iomanip>      // std::setw
#include <bits/stdc++.h>


std::string grid[2001][2001];

std::string merger(std::string s1, std::string s2, std::string merged){
    if(s1.length() + s2.length() != merged.length()){
        std::cout << "empty grid" << std::endl;
        return "*** NOT A MERGE ***";
    }
    int s1l = s1.length() +1;
    int s2l = s2.length() +1;
    std::locale loc;

    //accross in string2
    //down is string 1 
    //loop through grid
    for(int i = 0; i < s1l; i++){
        for(int j = 0; j < s2l; j++){
            if (i == 0 && j == 0) {
                grid[i][j] = "";
            } else if (i == 0) {

                if(grid[i][j - 1] != "0" && s2.at(j - 1) == merged.at(i + j - 1)){
                    grid[i][j] = grid[i][j - 1] + s2.at(j - 1);
                }else{
                    grid[i][j] = "0";
                }

            } else if (j == 0) {
                 if(grid[i - 1][j] != "0" && s1.at(i - 1) == merged.at(i + j - 1)){
                    grid[i][j] = grid[i - 1][j] + std::toupper(s1.at(i - 1),loc);
                }else{
                    grid[i][j] = "0";
                }
            } else {
                bool flag = true;
                if((grid[i][j - 1] != "0"  && s2.at(j - 1) == merged.at(i + j - 1))){
                    grid[i][j] = grid[i][j - 1] + s2.at(j - 1);
                    flag = false;
                }
                if(grid[i - 1][j] != "0" && s1.at(i - 1) == merged.at(i + j - 1) && flag){
                    grid[i][j] = grid[i - 1][j] + std::toupper(s1.at(i - 1),loc);
                    flag = false;
                }
                if(flag){
                    grid[i][j] = "0";
                }

            }
        }
    }
    std::string out = grid[s1l-1][s2l-1];

    std::cout << "|--------------------------------------------------------------|" <<std::endl;
    //print out the grid
    for(int i = 0; i < s1l; i++){
        for(int j = 0; j < s2l; j++){
            std::cout << std::setw(merged.size()+2) << grid[i][j] << " ";
            // grid[i][j] = "";
        }
        std::cout << "|" <<std::endl;
    }
    std::cout << "|--------------------------------------------------------------|" <<std::endl;


    if(out == "" || out == "0"){
        return "*** NOT A MERGE ***";
    }
    return out;
}


int main() {
    //ask the user for name of file
    std::cout << "Enter the name of the input file: ";
    std::string fileName;
    std::cin >> fileName;
    //open the file
    std::ifstream inFile(fileName);
    //check if file is open
    if (!inFile) {
        std::cout << "Error opening the input file" << std::endl;
        return 1;
    }

    //ask the user for name of output file
    std::cout << "Enter the name of the output file: ";
    std::string outFileName;
    std::cin >> outFileName;
    //open the file
    std::ofstream outFile;
    outFile.open(outFileName);
    //check if file is open
    if (!outFile) {
        std::cout << "Error opening the output file" << std::endl;
        return 1;
    }

    //create a vector of strings 
    std::vector<std::string> words;
    words.resize(3);
    int i = 0;

    //read the file
    std::string s1;
    std::string s2;
    std::string s3;

    while (true) {
        std::getline(inFile, s1);
        bool s1True = inFile.eof();
        std::getline(inFile, s2);
        bool s2True = inFile.eof();
        std::getline(inFile, s3);
        bool s3True = inFile.eof();
       if(!s1True || !s2True || !s3True) {
            std::cout << merger(s1, s2, s3) << std::endl;
            s1 = "";
            s2 = "";
            s3 = "";
       }else{
           break;
       }
    }
}