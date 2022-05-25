#include <iostream>
#include <string>
#include "Graph.h"

int main()
{

    const std::string source = "GraphInput.txt";
    Graph G;
    G.readFromFile(source);
    std::cout << "ODCZYT GRAFU G: " << std::endl;
    G.printGraph();

    std::cout << "GRAF SPRZĘZONY: " << (G.isAdjointGraph() ? "TAK" : "NIE") << std::endl;
    std::cout << "GRAF LINIOWY: " << (G.isLinearGraph() ? "TAK" : "NIE") << std::endl;
    if (G.isAdjointGraph() == 1)
    {
        std::cout << "TRANSLACJA DO GRAFU H: " << std::endl;
        G.translate();
    }
}