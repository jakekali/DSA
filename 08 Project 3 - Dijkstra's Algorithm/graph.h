#include <iostream>
#include <vector>
#include <list>
#include "heap.h"


class graph{
    public: 
    // Constructor that initializes the graph
    graph(int numVertices);

    //Inserts a new vertex
    void insertVertex(const std::string &id, const std::string &id2, int w);

    //Use Dijkstra's algorithm to find the shortest path from start to all other vertices
    // return -1 if starting vertex is not found
    int DoDijkstra(const std::string &start);

    //write the shortest path from start to end to the output stream
    //if the path is known, returns vertex name, the path distance and the path
    //otherwise, returns vertex name and "no path"
    void printGraph(std::string outFileName);

    //If the vertice name is in the graph, return true, else return false
    bool isInGraph(const std::string &id);


    //Prints the Current Table State of the List of Vertices
    void printTable();

    private:
    class node;
    //Private Edge Class
    class edge{
        public:
        node* destination;
        int weight;
    };



    //Private Node Class
    class node{
        public:
        std::string name; 
        std::string path; 
        int distance = 2000000;
        bool known = false;
        std::list<edge> edges;
    };

    //List of Vertices tha are being inserted into the
    std::list<node> nodes;
    int vertices = 0;

    hashTable table; 
};