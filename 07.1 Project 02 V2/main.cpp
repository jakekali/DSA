#include <iostream>
#include "heap.h"
#include "hash.h"
using namespace std;

int main() {
    cout << "Testing \n";
    std::string pizza = "pizza";
    heap jacob = heap(360);
    cout << "Heap Created \n";
    cout << jacob.getCapacity() << '\n';
    jacob.insert("15",15,&pizza);
    jacob.insert("5",5,&pizza);
    jacob.insert("3",3,&pizza);
    jacob.insert("7",7,&pizza);
    jacob.setKey("7",89);
    cout << "Inserted into heap \n";
    cout << jacob.getArray();
    return 0;
}