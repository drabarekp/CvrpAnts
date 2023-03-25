#include "NetworkGraph.h"
#include <iostream>
#include <stdexcept>

NetworkGraph::NetworkGraph(CostMatrix& cost_matrix)
{
	if (cost_matrix.size() <= 0)
		throw std::runtime_error("error");

	if (cost_matrix.size() != cost_matrix[0].size())
		throw std::runtime_error("error");

	this->costs = cost_matrix;
}

double NetworkGraph::getCost(int i, int j) const {
	if(i < j)
		return costs[i][j];

	return costs[j][i];
}

int NetworkGraph::verticesCount() const {
	return costs.size();
}

int NetworkGraph::edgesCount() const {

	int count = 0;

	for (int i = 0; i < verticesCount(); i++) {
		for (int j = 0; j < verticesCount(); j++) {
			if (getCost(i, j) != NO_EDGE) count++;
		}
	}

	return count / 2;
}

std::string NetworkGraph::toString() const {

	std::string result;

	for (int i = 0; i < verticesCount(); i++) {
		for (int j = 0; j < verticesCount(); j++) {
			result.append(std::to_string(getCost(i, j)) + " ");
		}
		result.append("\n");
	}

	return result;
}

