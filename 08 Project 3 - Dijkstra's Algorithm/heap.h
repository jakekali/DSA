
#include <vector>
#include <string>
#include "hash.h"
#include <bits/stdc++.h>

// 
class heap{
  public: 
  //
  // heap - The constructor allocates space for the nodes of the heap
  // and the mapping (hash table) based on the specified capacity
  //
  heap(int capacity);

  //
  // insert - Inserts a new node into the binary heap
  //
  // Inserts a node with the specified id string, key,
  // and optionally a pointer.  They key is used to
  // determine the final position of the new node.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is already filled to capacity
  //   2 if a node with the given id already exists (but the heap
  //     is not filled to capacity)
  //
  int insert(const std::string &id, int key, void *pv = nullptr);

  //
  // setKey - set the key of the specified node to the specified value
  //
  // I have decided that the class should provide this member function
  // instead of two separate increaseKey and decreaseKey functions.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist
  //
  int setKey(const std::string &id, int key);

  //
  // deleteMin - return the data associated with the smallest key
  //             and delete that node from the binary heap
  //
  // If pId is supplied (i.e., it is not nullptr), write to that address
  // the id of the node being deleted. If pKey is supplied, write to
  // that address the key of the node being deleted. If ppData is
  // supplied, write to that address the associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is empty
  //
  int deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);

  //
  // remove - delete the node with the specified id from the binary heap
  //
  // If pKey is supplied, write to that address the key of the node
  // being deleted. If ppData is supplied, write to that address the
  // associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist
  //
  int remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr);
    //getHeapOrder()
    //prints a copy of the heap with elements
  std::string drawHeap();
  std::string getArray();
  int getCapacity(){return capacity;};
  int getCurrSize(){return this->currentSize;};
  hashTable map_p; // maps ids to nodes



  private:
  class heap_node{
    private: 
      std::string id; // The id of this node
      int key = INT_MIN; // The key of this node
      void *pData; // A pointer to the actual data
    public:
      heap_node(){};
      heap_node(std::string id_n, int key_n, void *pData_n){
        id = id_n;
        key = key_n;
        this->pData = pData_n;
      }

      void setKey(int newKey){this->key = newKey;}
      int getKey(){return this->key;};
      std::string getID(){return this->id;};
      void* getData(){ return this->pData;};
      

      std::string printNode(){
          return "Key: " + std::to_string(this->key) + '\n' + "ID: " + this->id + '\n';
      }

  };
  private:
  std::vector<heap_node> data; // The actual binary heap

  int capacity; // Capacity of the heap
  int currentSize; // Current size of the heap

 int getPos(void* id);

  //Heapify Down
  // return 0 on success, and 1 on failure
  int heapifyDown(int posCur = 1);

  //Heapify Up
  // return 0 on success, and 1 on failure
  int heapifyUp(int posCur);
  
};
