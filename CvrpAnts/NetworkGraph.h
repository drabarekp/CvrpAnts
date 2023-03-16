#pragma once
#include <vector>

typedef std::vector<std::vector<double>> CostMatrix;

class NetworkGraph{

	const int NO_EDGE = INT_MIN;
private:
	CostMatrix costs;

public:
	NetworkGraph(CostMatrix& cost_matrix);

	double getCost(int i, int j) const;
	int edgesCount() const;
	int verticesCount() const;
};