#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <string>
#include <vector>

class Edge
{
public:
    int sourceID;
    int destID;
    Edge(int sourceID, int destID)
    {
        this->sourceID = sourceID;
        this->destID = destID;
    }
};

#endif