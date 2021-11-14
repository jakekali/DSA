#include "graph.h"
#include <iostream>

int main(){
    //ask the user to enter the name of file to specify the graph
    std::cout << "Enter the name of the file to specify the graph: ";
    std::string inFileName;
    std::cin >> inFileName;

    //open fileName
    std::ifstream inFile(inFileName);
    if(!inFile){
        std::cout << "Error: file not found" << std::endl;
        return 1;
    }

    graph g = graph(500);
    
    //loop through the file and add edges to the graph
    std::string line;
    while(std::getline(inFile, line)){
        std::stringstream ss(line);
        std::string from;
        std::string to;
        std::string weight;
        std::getline(ss, from, ' ');
        std::getline(ss, to, ' ');
        std::getline(ss, weight);
        g.insertVertex(from, to, std::stoi(weight));
    }
    std::string start;

    while(1){
        //ask the user to enter a starting index
        std::cout << "Enter the starting index: ";
        std::cin >> start;

        //check if the starting index is in the graph
        if(!g.isInGraph(start)){
            std::cout << "\n Error: starting index not found" << std::endl;
        }else{
            break;
        }
    }

    //get cpu time
    auto start_t = std::chrono::high_resolution_clock::now();
    g.DoDijkstra(start);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start_t;
    std::cout << "Total time (in seconds) for Dijkstra's Algorithm : " << elapsed.count() << " s" << std::endl;


    //ask the user for output file name
    std::cout << "Enter the name of the output file: ";
    std::string outFileName;
    std::cin >> outFileName;

    //open output file
    g.printGraph(outFileName);
    return 0;
}
