#include "hash.h"
#include "heap.h"
#include <iostream>

heap::heap(int capacity){
    this->data.resize(capacity + 1);
    this->capacity = capacity;
    this->currentSize = 0;
}

int heap::insert(const std::string &id, int key, void *pv) {
    if(key == 7){
        std::cout << "greg";
    }
    // if too big
    if (capacity <= currentSize) { return 1; }
    node *new_node = new node(id, key, pv);
    std::cout << new_node->printNode();    
    currentSize++;
    data[currentSize] = (new_node);    
   // auto pv = &data[currentSize];
    if(mapping.insert(id, &data[currentSize])){ return 2;} //if rehash failed or key exists already
    mapping.insert("00000000000", &data[0]);
    mapping.insert("id", &data[1]);

    //void* b = mapping.getPointer(id);
    bool t;
    bool f;
    node *pn = static_cast<node *> (mapping.getPointer("id", &t));
    node *pn2 = static_cast<node *> (mapping.getPointer("00000000000"));

    std::string y = typeid(pn).name();
    std::string z = typeid(pn2).name();

    

    heapifyUp(currentSize);
    return 0; 
}

int heap::setKey(const std::string &id, int key) {
    void* x = mapping.getPointer(id);
    int pos = ( std::vector<node*>* )x - &data;  //Calculate the position of the indicated node
    //int old_key = x->getKey();
   // x->setKey(key);
    //if (old_key > key) {
    //    heapifyDown();
 //   }
  
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
    if (currentSize == 0)
        return 1;
    if(pId != 0){ *pId = data[1]->getID(); } 
    if(pKey != 0){ *pKey = data[1]->getKey(); }
    if(ppData != 0){ ppData = data[1]->getData(); } //TODO Check that this works, bc it prob doesn't
    std::string ID = data[1]->getID(); // ID of min object
    data[1] = std::move(data[currentSize--]);
    heapifyDown(1);
    data[currentSize + 1] = nullptr;
    mapping.remove(ID);
    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData) {
    
}

std::string heap::drawHeap() {

}

std::string heap::getArray() {
    std::string x;
    for (int i = 1; i < currentSize; i++){
        x += "Current Node Index: " + i + '\n' + data[i]->printNode();
    }
    return x;
}

int heap::heapifyDown(int posCur) {
    int child;
    node* tmp = data[posCur];

    for(;posCur*2 <= currentSize; posCur = child){
        child = posCur*2;
        if(child != currentSize && data[child +1]->getKey() < data[child]->getKey())
            ++child;
        if(data[child]->getKey() < tmp->getKey()){
            data[posCur] = std::move(data[child]);
            mapping.setPointer(data[posCur]->getID(),&data[child]);
        }else
            break;
    }
    data[posCur] = std::move(tmp);
    mapping.setPointer(tmp->getID(),&data[posCur]);

}

int heap::heapifyUp(int posCur) {
    node* new_data = data[posCur];
    for(;posCur>1 && new_data->getKey() < data[posCur/2]->getKey();posCur/=2){
        data[posCur] = std::move(data[posCur/2]);
        mapping.setPointer(data[posCur]->getID(),&data[posCur/2]);
    }
    data[posCur] = std::move(new_data);
    mapping.setPointer(data[posCur]->getID(),&data[posCur]);
}


int heap::getPos(void *pn)
{
	int pos = ( std::vector<node*>* )pn - &data;  //Calculate the position of the indicated node
	return pos;
    
}