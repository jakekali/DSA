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
            return i;
    }
    return 201326611;
}

int hashTable::hash(const std::string &key){
    // P and M
    int p = 60;
    int m = this->capacity;
    long long power_of_p = 1;
    long long hash_val = 0;


    // Loop to calculate the hash value
    // by iterating over the elements of string
    for (int i = 0; i < key.length(); i++) {
        hash_val
                = (hash_val
                   + (key[i] - 'a' + 1) * power_of_p)
                  % m;
        power_of_p
                = (power_of_p * p) % m;
    }
    return hash_val;
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
        return 1;
    }

    int hashed_key = this->hash(key);
    int currentposition = hashed_key;
    while(this->data[currentposition].isOccupied && !this->data[currentposition].isDeleted) {
        if(currentposition >= this->capacity - 1){
            currentposition = 0;
        }else{
            currentposition++;
        }
    }
    this->data[currentposition].key = key;
    this->data[currentposition].isOccupied = true;
    this->data[currentposition].pv = pv;
    this->data[currentposition].isDeleted = false;
    return 0;

}

bool hashTable::contains(const std::string &key) {
    int hashedkey = this->hash(key);
    int currentposition = hashedkey;
    while(this->data[currentposition].isOccupied || !this->data[currentposition].isDeleted) {
        if(this->data[currentposition].key == key && !this->data[currentposition].isDeleted){
            return true;
        }
        if(!this->data[currentposition].isOccupied){
            return false;
        }
        if(currentposition >= this->capacity - 1){
            currentposition = 0;
        }else{
            currentposition++;
        }
    }
    return false;
}

bool hashTable::rehash() {
    // The rehash function; makes the hash table bigger.
    // Returns true on success, false if memory allocation fails.
    try{
        vector<hashItem> old_table = this->data;
        this->data = vector<hashItem>();
        this->capacity = this->getPrime(2*(this->capacity+5));
        this->data.resize(this->capacity);
        for (auto &&hash_item : old_table){
            if(hash_item.isOccupied && !hash_item.isDeleted){
                this->insert(hash_item.key,hash_item.pv);
            }
        }
    }catch(system_error){
        return false;
    }

    return false;
}


// Get the pointer associated with the specified key.
// If the key does not exist in the hash table, return nullptr.
// If an optional pointer to a bool is provided,
// set the bool to true if the key is in the hash table,
// and set the bool to false otherwise.
bool hashTable::*getPointer(const std::string &key, bool *b) {
    int pos = this->findPos(key);
    if(pos == -1){
        *b = false;
        return nullptr;
    }else{
        *b = true;
        return ;
    }


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
}


int main(){
    hashTable *hasher = new hashTable(0);
    cout << "\n" << hasher->insert("jakesigmin");
    cout << "\n" << hasher->insert("jakesigmin");
    cout << "\n" << hasher->insert("jakesigmin");
    cout << "\n" << hasher->insert("jakesigmin");
    cout << "\n" << hasher->insert("jakesigmin");
    cout << "\n" << hasher->insert("jakesigmin");
    cout << "\n" << hasher->insert("jakesigmin");
    cout << "\n" << hasher->contains("pizz");
    cout << "\n" << hasher->contains("jakesigmin");



};