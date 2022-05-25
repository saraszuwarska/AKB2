#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Graph.h"

bool contains(std::vector<int> &source, int el)
{
    for (int i = 0; i < source.size(); i++)
    {
        if (source[i] == el)
        {
            return true;
        }
    }
    return false;
}

bool areDisjointVectors(std::vector<int> &source, std::vector<int> &destination) //dobra praktyka to przekazywac adres oryginalnej zmiennej
// zeby odczytywac bezposrednio z miejsca pamieci
{
    for (int id = 0; id < source.size(); id++)
    {
        if (contains(destination, source[id]))
        {
            return false;
        }
    }
    return true;
}

bool areAlikeVectors(std::vector<int> &source, std::vector<int> &destination)
{
    if (source.size() != destination.size())
    {
        return false;
    }
    for (int index = 0; index < source.size(); index++)
    {
        if (source[index] != destination[index])
        {
            return false;
        }
    }
    return true;
}

void Graph::readFromFile(std::string fileName)
{
    int id = 0;
    std::string line;
    std::ifstream ist(fileName); //utworzenie strumienia wejsciowego
    if (!ist)
    {
        std::cout << "Niepowodzenie" << std::endl;
    }
    else
    {

        while (getline(ist, line))
        {
            std::istringstream is(line); //utworzenie strumienia ze zczytanej linii tekstu
            this->adjList.push_back(std::vector<int>(std::istream_iterator<int>(is), std::istream_iterator<int>()));
            std::sort(this->adjList[id].begin(), this->adjList[id].end());
            id++;
        }
    }
    this->createPredList();
    this->translateEdges();
}
void Graph::printGraph()
{
    std::cout << "LISTA NASTEPNIKOW: " << std::endl;
    for (int i = 0; i < this->adjList.size(); i++)
    {
        std::cout << "# Wierzchołka: " << i << std::endl;
        for (int j = 0; j < this->adjList[i].size(); j++)
        {
            std::cout << this->adjList[i][j] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    std::cout << "LISTA POPRZEDNIKOW: " << std::endl;
    for (int k = 0; k < this->adjPredList.size(); k++)
    {
        std::cout << "# Wierzchołka: " << k << std::endl;
        for (int l = 0; l < this->adjPredList[k].size(); l++)
        {
            std::cout << this->adjPredList[k][l] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    std::cout << "LISTA KRAWEDZI: " << std::endl;
    for (int i = 0; i < edges.size(); i++)
    {
        std::cout << "# W. zrodlowy: " << this->edges[i].sourceID << std::endl;
        std::cout << "Do: " << this->edges[i].destID << std::endl;
    }
}

bool Graph::isAdjointGraph()
{
    bool isAdjoint = true;
    for (int src_id = 0; src_id < this->adjList.size(); src_id++)
    {
        for (int dest_id = 0; dest_id < this->adjList.size(); dest_id++)
        {
            if (src_id != dest_id)
            {
                isAdjoint = (areDisjointVectors(this->adjList[src_id], this->adjList[dest_id]) || areAlikeVectors(this->adjList[src_id], this->adjList[dest_id]));
                if (!isAdjoint)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void Graph::createPredList()
{
    this->adjPredList.resize(this->adjList.size());
    for (int src_id = 0; src_id < this->adjList.size(); src_id++) //kojarzony index
    {
        for (int vert_id = 0; vert_id < this->adjList.size(); vert_id++) // wierzch pionowe
        {
            for (int dest_id = 0; dest_id < adjList[vert_id].size(); dest_id++) //nastepniki
            {
                if (this->adjList[vert_id][dest_id] == src_id)
                {
                    this->adjPredList[src_id].push_back(vert_id);
                }
            }
        }
    }
}
bool Graph::isLinearGraph()
{
    bool isLinear = true;
    for (int src_id = 0; src_id < this->adjList.size(); src_id++)
    {
        for (int dest_id = 0; dest_id < this->adjList.size(); dest_id++)
        {
            if (src_id != dest_id)
            {
                isLinear = (areDisjointVectors(this->adjList[src_id], this->adjList[dest_id]) || (areAlikeVectors(this->adjList[src_id], this->adjList[dest_id]) && areDisjointVectors(this->adjPredList[src_id], this->adjPredList[dest_id])));
                if (!isLinear)
                {
                    return false;
                }
            }
        }
    }
    return true;
}
void Graph::translateEdges()
{
    for (int i = 0; i < adjList.size(); i++)
    {
        for (int j = 0; j < adjList[i].size(); j++)
        {
            this->edges.push_back(Edge(i, this->adjList[i][j]));
        }
    }
}

void Graph::changeOccur(int changefrom, int changeto)
{
    for (int edgeID = 0; edgeID < this->edges.size(); edgeID++)
    {
        if (this->edges[edgeID].sourceID == changefrom)
        {
            this->edges[edgeID].sourceID = changeto;
        }
        if (this->edges[edgeID].destID == changefrom)
        {
            this->edges[edgeID].destID = changeto;
        }
    }
}

void Graph::translate()
{
    Graph H;
    int sourceEdge;
    int destEdge;
    for (int src_id = 0; src_id < this->adjList.size(); src_id++)
    {
        H.edges.push_back(Edge(2 * src_id, 2 * src_id + 1));
    }
    for (int sourceEdgeID = 0; sourceEdgeID < this->edges.size(); sourceEdgeID++)
    {
        int changefrom = H.edges[this->edges[sourceEdgeID].destID].sourceID;
        int changeto = H.edges[this->edges[sourceEdgeID].sourceID].destID;
        H.changeOccur(changefrom, changeto);
    }

    std::vector<int> vertices;
    for (int edgeID = 0; edgeID < H.edges.size(); edgeID++)
    {
        if (!contains(vertices, H.edges[edgeID].sourceID))
        {
            vertices.push_back(H.edges[edgeID].sourceID);
        }
        if (!contains(vertices, H.edges[edgeID].destID))
        {
            vertices.push_back(H.edges[edgeID].destID);
        }
    }
    for (int vID = 0; vID < vertices.size(); vID++)
    {
        H.changeOccur(vertices[vID], vID);
    }
    H.adjList.resize(vertices.size());
    H.adjPredList.resize(vertices.size());
    H.translateOutput();
    H.createPredList();
    H.printGraph();
    H.saveToFile("OutputFile.txt");
}
void Graph::translateOutput()
{
    for (int edgeID = 0; edgeID < this->edges.size(); edgeID++)
    {
        this->adjList[this->edges[edgeID].sourceID].push_back(this->edges[edgeID].destID);
    }
}

void Graph::saveToFile(std::string fileName)
{
    std::ofstream outfile;
    outfile.open(fileName);

    std::cout << "ZAPISANO GRAF H" << std::endl;
    for (int i = 0; i < this->adjList.size(); i++)
    {
        for (int j = 0; j < this->adjList[i].size(); j++)
        {
            outfile << this->adjList[i][j] << " ";
        }
        outfile << std::endl;
    }
    outfile.close();
}

Graph::Graph()
{
}