#include "graph.h"
#include <iostream>

//
// Constructor
graph::graph(int numVertices){
    table = hashTable(numVertices*2);

}

//Insert a vertex into the graph
void graph::insertVertex(const std::string &id, const std::string &id2, int w){
    bool b1, b2;
    node *vertex1Location;
    //Check if Starting Vertex is in the graph
    if(!this->table.contains(id)){
        //Create a new node
        node N; 
        N.name = id;
        nodes.push_back(N);
        table.insert(id, &(nodes.back()));
        vertex1Location = &(nodes.back());
        vertices++;
    }else{
        vertex1Location = static_cast<node*>(table.getPointer(id,&b1));
    }

    node *vertex2Location;
    //Check if Ending Vertex is in the graph
    if(!this->table.contains(id2)){
    //Create a new node
        node N2; 
        N2.name = id2;
        nodes.push_back(N2);
        table.insert(id2, &(nodes.back()));
        vertex2Location = &(nodes.back());
        vertices++;
    }else{
        vertex2Location = static_cast<node*>(table.getPointer(id2,&b2));
    }

    //Create a new edge from starting vertex to ending vertex
    edge E;
    E.weight = w;
    E.destination = vertex2Location;
    vertex1Location->edges.push_back(E);
}

bool graph::isInGraph(const std::string &id){
    return this->table.contains(id);
}

int graph::DoDijkstra(const std::string &id){
    
    heap minHeap = heap(vertices);
    //Set all vertices to known 
    // nodes is a std::list<node>

	for (auto it = nodes.begin(); it != nodes.end(); it++)
	{
        if(it->name == id){
            it->distance = 0;
        }else{
            it->distance = 2000000;
        }
		minHeap.insert((*it).name, (*it).distance, &(*it));
	}


    //Get the starting vertex
    bool b1;
    node *start = static_cast<node*>(table.getPointer(id,&b1));
    if(!b1){
        return -1;
    }
    minHeap.setKey(id,0);

    std::cout << "Intial Configuration" << std::endl;
    printTable();

    //Min Heap
    for(;;){
        std::string pID;
        int pkey;
        void* pNode;

        minHeap.deleteMin(&pID, &pkey, &pNode);
        node *smallDistanceNode = (graph::node*)pNode;
        if(smallDistanceNode->known){
            break;
        }
        smallDistanceNode->known = true;
        for(auto e = smallDistanceNode->edges.begin(); e !=  smallDistanceNode->edges.end(); e++){
            if(!(*e).destination->known){
                int newDistance = smallDistanceNode->distance + e->weight;
                if(newDistance < (*e).destination->distance){
                    (*e).destination->distance = newDistance;
                    (*e).destination->path = smallDistanceNode->path + (smallDistanceNode->name + ", ");
                    minHeap.setKey((*e).destination->name, (*e).destination->distance);
                }
            }
        }
        
        std::cout << "After Evaluation of " <<smallDistanceNode->name << std::endl;
        printTable();
        std::cout << std::endl;
    }
}


void graph::printGraph(std::string outFileName){
    std::ofstream outFile(outFileName);
    for(node n : nodes){
        if(n.distance < 1100000){
            outFile << n.name << ": " << std::to_string(n.distance) << " [" << n.path << n.name << "]" << std::endl;; 
        }else{
            outFile << n.name << ": NO PATH\n";// << std::to_string(n.distance) << " [" << n.path << n.name << "]" << std::endl;; 
        }

    }
    outFile.close();
}


void graph::printTable(){
    std::cout <<"| V# | known | Distance | Path          |" << std::endl;
    for(auto item = nodes.begin(); item != nodes.end(); ++item){
        if(item->distance > 1100000){
            std::cout <<"| "<<  item->name << " | " << item->known << " | I | " << item->path << " |" << std::endl;
        }else{
            std::cout <<"| "<<  item->name << " | " << item->known << " | "<< item->distance << " | " << item->path << " |" << std::endl;
        }
    }
}