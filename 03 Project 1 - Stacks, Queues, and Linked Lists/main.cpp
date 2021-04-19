#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
#include <map>

// To avoid extra typing:
using namespace std;

//An Abstract Templated linkList Class:
template <typename Data>
class linkList{

    //A Node Class Contained Within:
    class Node{
    private:
        Data data;
        Node* next;

    public:
        Node(Data fruit){ data = fruit; next = NULL;};
        Node(Data fruit, Node* adv){ data = fruit; next = adv;}
        Data getData(){ return data; };
        Node* getNext(){ return next; };
        void setNext(Node* adva){ next = adva;};
    };

private:
    Node *first;
    Node *last;
    int size;

public:
    int getSize(){ return size; }
    linkList(){first = NULL; last = NULL; size = 0;};
    virtual void push(Data addMe) = 0;
    virtual Data pop() = 0;

protected:
    void insertAtStart(Data addMeStart);
    void insertAtEnd(Data addMeEnd);
    Data removeFromStart();

};

template<typename Data>
void linkList<Data>::insertAtStart(Data addMeStart) {
    linkList::Node* addMe = new Node(addMeStart);
    if (size == 0){
        last = addMe;
    }else{
        addMe->setNext(first);
    }
    first = addMe;
    size++;

}

template<typename Data>
void linkList<Data>::insertAtEnd(Data addMeEnd) {
    linkList::Node* addMe = new Node(addMeEnd);
    if (size == 0){
        first = addMe;
    }else{
        last->setNext(addMe);
    }
    last = addMe;
    size++;
}

template<typename Data>
Data linkList<Data>::removeFromStart() {

    if(size == 0){
        first = nullptr;
        last = nullptr;
        return 0;
    }
    auto tmpNode = first;
    Data sendMe = tmpNode->getData();
    if(size == 1){
        first = nullptr;
        last = nullptr;
    }else {
        first = tmpNode->getNext();

    }
    size--;
    delete tmpNode;

    return sendMe;
}


//Inherited Stack Class:
template<typename Data>
class Stack: public linkList<Data>{
public:
    void push(Data addMeStack){return this->insertAtStart(addMeStack);};
    Data pop(){ return this->removeFromStart();};
};


//Inherited Queue Class:
template<typename Data>
class Queue: public linkList<Data>{
public:
    void push(Data addMeQueue){return this->insertAtEnd(addMeQueue);};
    Data pop(){ return this->removeFromStart(); };
};

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

class Handler{
private:
    map<string, linkList<int> *> intMap;
    map<string, linkList<double> *> doubleMap;
    map<string, linkList<string> *> stringMap;




public:
    ofstream outputF;
    ifstream inputF;
    void create(string name, const string& type);
    void push(string name, string addMe);
    void pop(string name);
    bool exist(string name);
    void proccess();
    static vector<string> split(const string &s, char delim);
};

vector<string> Handler::split(const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
};


bool Handler::exist(string name) {
    if (name[0] == 'i'){
        //ints here
        if (intMap.end() == intMap.find(name)){
            return false;
        } else{
            return true;
        }
    }else if (name[0] == 'd'){
        if (doubleMap.end() == doubleMap.find(name)){
            return false;
        } else{
            return true;
        }

    }else if (name[0] == 's'){
        //string here
        if (stringMap.end() == stringMap.find(name)){
            return false;
        } else{
            return true;
        }
    }else{
        return false;
    }
}

void Handler::proccess(){
    string command;
    while(getline(inputF,command)){
        outputF << "PROCESSING COMMAND: " << command << '\n';
        auto words = this->split(command, ' ');

        //Go Through The Commands:
        if(words[0] == "create"){
            this->create(words[1],words[2]);
        }else if (words[0] == "push"){
            this->push(words[1],words[2]);
        }else if (words[0] == "pop"){
            this->pop(words[1]);
        }
    }
}

//Create
void Handler::create(string name, const string& type) {
    if(this->exist(name)){
        outputF << "ERROR: This name already exists!" << "\n";
        return;
    }
    if (name[0] == 'i'){
        //ints here
        if (type == "queue"){
            intMap.insert(pair<string, linkList<int> *>(name, new Queue<int>()));
        }else if (type == "stack"){
            intMap.insert(pair<string, linkList<int> *>(name, new Stack<int>()));
        }
    }else if (name[0] == 'd'){
        // doubles here
        if (type == "queue"){
            doubleMap.insert(pair<string, linkList<double> *>(name, new Queue<double>()));
        }else if (type == "stack"){
            doubleMap.insert(pair<string, linkList<double> *>(name, new Stack<double>()));
        }
    }else if (name[0] == 's'){
        //string here
        if (type == "queue"){
            stringMap.insert(pair<string, linkList<string> *>(name, new Queue<string>()));
        }else if (type == "stack"){
            stringMap.insert(pair<string, linkList<string> *>(name, new Stack<string>()));
        }

    }
}

void Handler::push(string name, string addMe) {
    if(this->exist(name)){
        if (name[0] == 'i'){
            intMap[name]->push(stoi(addMe));
        }else if (name[0] == 'd'){
            double test = stod(addMe);
            doubleMap[name]->push(test);
        }else if (name[0] == 's'){
            stringMap[name]->push(addMe);
        }else{
            outputF <<  "ERROR: This name does not exist! \n";
            return;
        }}else{
            outputF <<  "ERROR: This name does not exist! \n";
    }
}

void Handler::pop(string name) {
    if(this->exist(name)){
        if (name[0] == 'i'){
            if (0 == intMap[name]->getSize()){
                outputF << "ERROR: This list is empty!" << "\n";
            }else{
                outputF << "Value popped: " << intMap[name]->pop() << "\n";
            }
        }else if (name[0] == 'd'){
            if (0 == doubleMap[name]->getSize()){
                outputF << "ERROR: This list is empty!" << "\n";
            }else{
                outputF << "Value popped: " << doubleMap[name]->pop() << "\n";
            }
        }else if (name[0] == 's'){
            if (0 == stringMap[name]->getSize()){
                outputF << "ERROR: This list is empty!" << "\n";
            }else{
                outputF << "Value popped: " << stringMap[name]->pop() << "\n";
            }
        }else{
            outputF << "ERROR: This name does not exist!" << "\n";
            return;
        }
    }else{
            outputF << "ERROR: This name does not exist!" << "\n";
    }

}


int main() {
    auto handle = new Handler;

    string input;
    string ouput;
    //Get Input File From User
    cout << "Input File Name: ";
    getline(cin, input);

    //Get Output File From User
    cout << "Output File Name: ";
    getline(cin, ouput);

    //Open File Streams From Use in the Class
    handle->inputF.open(input);
    handle->outputF.open(ouput);

    handle->proccess();

    handle->inputF.close();
    handle->outputF.close();
    return 0;
}