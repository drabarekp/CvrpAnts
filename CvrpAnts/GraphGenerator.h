#pragma once

#include "NetworkGraph.h"

class GraphGenerator {
	std::vector<std::vector<double>> generateCostMatrix(int verticesNum);

public:
	NetworkGraph generateUniformDistributionCostsGraph(int verticesNum, int seed);
};