#include "GraphGenerator.h"
#include <random>

std::vector<std::vector<double>> GraphGenerator::generateCostMatrix(int verticesNum) {

	std::vector<std::vector<double>> matrix(verticesNum);

	for (int i = 0; i < verticesNum; i++) {
		matrix[i].resize(verticesNum);
	}

	return matrix;
}

NetworkGraph GraphGenerator::generateUniformDistributionCostsGraph(int verticesNum, int seed) {
	auto costMatrix = generateCostMatrix(verticesNum);

	std::mt19937 gen(seed);
	std::uniform_real_distribution<> dis(0.1, 4.0);

	for (int i = 0; i < verticesNum; i++) {
		for (int j = i + 1; j < verticesNum; j++) {
			costMatrix[i][j] = dis(gen);
		}
	}

	NetworkGraph ng(costMatrix);
	return ng;
}