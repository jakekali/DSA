//
// Created by Jacob on 9/5/2021.
//

#include "hash.h"
#include <iostream>
using namespace std;


hashTable::hashTable(int size) {
    this->capacity = this->getPrime(size);
    this->filled = 0;
    this->data.resize(this->capacity);
}

unsigned int hashTable::getPrime(int size) {
    int primes []  = {193,389,769,1543,3079,6151,12289,24593,49157,98317,196613,393241,786433,1572869,3145739,6291469,12582917,25165843,50331653,100663319,201326611};
    for(int i : primes){
        if(i > size)
            return 41;
    }
    return 201326611;
}

int hashTable::hash(const std::string &key){
    unsigned int hashVal = 0;
    for (char ch : key)
        hashVal = 37*hashVal + ch;
    return hashVal % this->capacity;
}


int hashTable::insert(const std::string &key, void *pv) {
    // Insert the specified key into the hash table.
    // If an optional pointer is provided,
    // associate that pointer with the key.
    // Returns 0 on success,
    // 1 if key already exists in hash table,
    // 2 if rehash fails.
    if (capacity/2 < filled){
        if(!this->rehash()){
            return 2;
        }
    }

    if(this->contains(key)){
        this->duplicateKey++;
        return 1;
    }

    int hashed_key = this->hash(key);
    int currentposition = hashed_key;
    while(this->data[currentposition].isOccupied && !this->data[currentposition].isDeleted) {
        if(currentposition >= this->capacity - 1){
            currentposition = 0;
        }else{
            currentposition++;
            this->collCounter++;
        }
    }
    this->data[currentposition].key = key;
    this->data[currentposition].isOccupied = true;
    this->data[currentposition].pv = pv;
    this->data[currentposition].isDeleted = false;
    this->filled++;
    return 0;

}

bool hashTable::contains(const std::string &key) {
if(this->findPos(key) == -1){
    return false;
}
    return true;
}

bool hashTable::rehash() {
    rehashCounter++;
    // The rehash function; makes the hash table bigger.
    // Returns true on success, false if memory allocation fails.
    try{
        vector<hashItem> old_table = this->data;
        this->data = vector<hashItem>();
        this->capacity = this->getPrime(2*(this->capacity+5));
        this->data.clear();
        this->data.resize(this->capacity);
        this->filled = 0;
        this->duplicateKey = 0;
        for (auto &&hash_item : old_table){
            if(hash_item.isOccupied && !hash_item.isDeleted){
                this->insert(hash_item.key,hash_item.pv);
            }
        }
    }catch(system_error){
        return false;
    }
    return true;
}


int hashTable::findPos(const string &key) {
    int hashedkey = this->hash(key);
    int currentposition = hashedkey;
    while(this->data[currentposition].isOccupied || !this->data[currentposition].isDeleted) {
        if(this->data[currentposition].key == key && !this->data[currentposition].isDeleted){
            return currentposition;
        }
        if(!this->data[currentposition].isOccupied){
            return -1;
        }
        if(currentposition >= this->capacity - 1){
            currentposition = 0;
        }else{
            currentposition++;
        }
    }
    return -1;
}

bool hashTable::remove(const string &key) {
    int pos = this->findPos(key);
    if (pos == -1){
            return false;
    }else{
        this->data[pos].isDeleted = true;
        return true;
    }
    filled--;
}

void *hashTable::getPointer(const string &key, bool *b) {
    int position = this->findPos(key);

    if (b)
        *b = (position != -1);

    if (position == -1)
        return nullptr;

    return this->data[position].pv;
}

int hashTable::setPointer(const string &key, void *pv) {
    int pos = this->findPos(key);

    if (pos == -1)
        return 1;
    else{
        this->data[pos].pv = pv;
        return 0;
    }
}


