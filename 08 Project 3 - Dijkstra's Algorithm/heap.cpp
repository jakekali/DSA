#include "hash.h"
#include "heap.h"
#include <iostream>

heap::heap(int capacity){
    this->capacity = capacity;
    this->currentSize = 0;
    data.resize(capacity + 1);

}

int heap::insert(const std::string &id, int key, void *pv) {
    if(currentSize >= capacity){
        return 1;
    }else if(map_p.contains(id)){
        return 2;
    }else{
    heap_node new_node = heap_node(id, key, pv);

    int hole = ++currentSize;


    data[hole] = std::move(new_node);
    map_p.insert(data[hole].getID(),&data[hole]);

    heapifyDown(hole);
    return 0;
    
    //Simplier just to do it here, since it only 1 loop
    // it avoids an extra copying of the data
    // for(; new_node.getKey() < data[hole/2].getKey(); hole /= 2){
    //     data[hole] = std::move(data[hole/2]);
    //     map_p.setPointer(data[hole].getID(),&data[hole]);
    // }
    // data[hole] = std::move(new_node);
    // map_p.insert(data[hole].getID(),&data[hole]);
    }
}



int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
    if (currentSize == 0)
        return 1;
    if(pId != 0){ *pId = data[1].getID(); } 
    if(pKey != 0){ *pKey = data[1].getKey(); }
    if(ppData != 0){   *(static_cast<void **> (ppData)) = data[1].getData(); } //TODO Check that this works, bc it prob doesn't
    std::string ID = data[1].getID(); // ID of min object
    data[1] = std::move(data[currentSize--]);
    map_p.setPointer(data[1].getID(),&data[1]);
    heapifyDown(1);
    data[currentSize + 1] = heap_node();
    map_p.remove(ID);
    return 0;
}

int heap::heapifyDown(int posCur) {
    int child;
    heap_node tmp = data[posCur];

    for(;posCur*2 <= currentSize; posCur = child){
        child = posCur*2;
        if(child != currentSize && data[child +1].getKey() < data[child].getKey())
            ++child;
        if(data[child].getKey() < tmp.getKey()){
            data[posCur] = std::move(data[child]);
            map_p.setPointer(data[posCur].getID(),&data[posCur]);
        }else
            break;
    }
    data[posCur] = std::move(tmp);
    map_p.setPointer(data[posCur].getID(),&data[posCur]);
}

int heap::setKey(const std::string &id, int key){
    bool b;
    void* ptr = map_p.getPointer(id,&b);
    if(!b){
        return 1;
    }
    heap_node *old_node = static_cast<heap_node *> (ptr);
    int new_pos = old_node - &data[0] ;

    // if the key was increased
    int old_key = data[new_pos].getKey();
    data[new_pos].setKey( key);
    if (old_key > key){
        data[0] = std::move(*old_node);
        map_p.setPointer(old_node->getID(),&data[0]);
        heapifyUp(new_pos);
    }else{
        heapifyDown(new_pos);
    }
    data[0] = heap_node();
    return 0;
}

int heap::heapifyUp(int posCur){
	for (; data[0].getKey() < data[posCur / 2].getKey(); posCur /= 2)
	{
		data[posCur] = std::move(data[posCur / 2]);
		map_p.setPointer(data[posCur].getID(), &data[posCur]);
	}
	data[posCur] = std::move(data[0]);
	map_p.setPointer(data[posCur].getID(), &data[posCur]);
    data[0] = heap_node();
    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData){
    if(!map_p.contains(id)){
        return 1;
    }

    bool b; 
    heap_node *ptr = static_cast<heap_node *> (map_p.getPointer(id, &b)); 
	int pos = ptr - &data[0];

	if (pKey != nullptr)
	{
		*pKey = data[pos].getKey();
	}
	if (ppData != nullptr)
	{
		*(static_cast<void**>(ppData)) = data[pos].getData();
	}

	setKey(id, data[1].getKey()-10);
	deleteMin();

	return 0;
}