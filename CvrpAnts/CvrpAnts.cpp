// CvrpAnts.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "NetworkGraph.h"
#include "GraphGenerator.h"
#include "AntAlgorithm.h"

int main()
{
    GraphGenerator gg;
    auto ng = gg.generateUniformDistributionCostsGraph(20, 9999);
    std::vector<double> demands = { 1, 2, 3, 2, 1, 1, 2, 3, 4, 5, 3, 2, 3, 4, 4, 3, 2, 1, 1, 2 };
    AntAlgorithm aa(16.0, 200, ng, demands);
    aa.basicAntCvrp(0.0, 1.0, 0.1, 9999, 100000);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
