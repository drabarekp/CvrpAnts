#pragma once
#include "NetworkGraph.h"
#include <random>

class AntAlgorithm {

	//parameters:
	double capacity;
	int maxPathSize;
	NetworkGraph costGraph;
	std::vector<double> demands;

	double alpha = -1.0;
	double beta = -1.0;
	double pheromoneEvaporationCoefficient = -1.0;

	std::vector<std::vector<double>> pheromoneConcentration;
	std::mt19937 randomGenerator;


public:
	AntAlgorithm(double capacity, int maxPathSize, NetworkGraph costGraph, std::vector<double> demands) :
		capacity(capacity), maxPathSize(maxPathSize), costGraph(costGraph), demands(demands) {}

	void basicAntCvrp(double alpha, double beta, double pheromoneEvapotationCoefficient, int seed, int numberOfIterations);

private:
	std::vector<std::vector<int>> findSolution();
	std::vector<int> findPath(std::vector<bool>& visited);
	int chooseVertex(int currentVertex, std::vector<bool>& visited);
	double calculateLikelihoodFactorOfChoosingVertex(int currentVertex, int candidateVertex, bool visited);
	void updatePheromone(int from, int to, double deltaPheromone);
	void updatePheromoneOnPath(std::vector<int> path, double deltaPheromone);

	bool isCorrectSolution(std::vector<std::vector<int>> solution);
	double solutionCost(std::vector<std::vector<int>> solution); 
	void evaporatePheromone();

};