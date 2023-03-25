#pragma once
#include <vector>
#include <string>

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
	
	template<typename T>
	std::vector<std::vector<T>> getMatrix() const;

	std::string toString() const;
};

template<typename T>
std::vector<std::vector<T>> NetworkGraph::getMatrix() const {
	int verticesNum = verticesCount();
	std::vector<std::vector<T>> matrix(verticesNum);

	for (int i = 0; i < verticesNum; i++) {
		matrix[i].resize(verticesNum);
	}

	return matrix;
}