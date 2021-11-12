#include <iostream>
#include "heap.h"
#include "hash.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
using namespace std;

int main() {
    cout << "Testing \n";
    std::string pizza = "pizza";
    heap jacob = heap(500);
    cout << "Heap Created \n";    
   
std::string stringTmp = "";
int key = 0; 
int i = 20;

vector<int> c; 
vector<int> vv; 
vector<int> ww;
for(int i = -250; i < 250; i++) {
    c.push_back(i);
    vv.push_back(i);
    ww.push_back(i);
}
std::random_shuffle(c.begin(), c.end());
std::random_shuffle(vv.begin(), vv.end());
std::random_shuffle(ww.begin(), ww.end());


for(int i = 0; i < 500; i++) {
    if(c[i] > 250){
        cout << "WTF BITCHES";
    }
    cout <<" 1 - " << c[i] <<  ": " << jacob.insert("the"+std::to_string(c[i]),vv[i] ,&pizza) << "\n";
}

for(int i = 0; i < 500; i++) {
    cout <<" 2 - " << ww[i] <<  ": " << jacob.setKey("the"+std::to_string(ww[i]),ww[i]) << "\n";
}

for(int i = -250; i < 250; i++) {
    std::string cc;// = "the"+std::to_string(i);
    cout <<" 3 - "<< i << "  : " << jacob.deleteMin(&cc,&key) << "\n"; 
    cout <<" 3 - "<< i << ".1: " << "Key: " << key << "\n"; 
    cout <<" 3 - "<< i << ".2: " << "String: " << cc << "\n";

}
    return 0;
}