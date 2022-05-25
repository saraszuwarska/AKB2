#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include <iostream>
#include <string>
#include <vector>

class Graph
{
private:
    std::vector<std::vector<int> > adjList;     //tablica list nastepnikow - wierzch wychodzące
    std::vector<std::vector<int> > adjPredList; //tablica list poprzednikow - wierzch wchodzące
    std::vector<Edge> edges;                    //tablica krawedzi

public:
    void readFromFile(std::string fileName);
    void printGraph();
    bool isAdjointGraph();
    void createPredList();
    bool isLinearGraph();
    void translateEdges();
    void translate();
    void changeOccur(int changefrom, int changeto);
    void translateOutput();
    void saveToFile(std::string fileName);

    Graph();
};

#endif