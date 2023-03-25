#include "AntAlgorithm.h"
#include <cmath>
#include <numeric>
#include <exception>
#include <iostream>

int AntAlgorithm::chooseVertex(int currentVertex, std::vector<bool>& visited) {
	double likelihoodFactorSum = 0.0;
	std::vector<double> likelihoods;

	for (int i = 0; i < costGraph.verticesCount(); i++) {			
		likelihoods.push_back(calculateLikelihoodFactorOfChoosingVertex(currentVertex, i, visited[i]));
	}

	auto sum = std::reduce(likelihoods.begin(), likelihoods.end());
	std::uniform_real_distribution<> dis(0.0, sum);
	double randomNum = dis(randomGenerator);
	double accumulator = 0.0;

	for (int i = 0; i < likelihoods.size(); i++) {
		accumulator += likelihoods[i];
		if (accumulator > randomNum) {
			return i;
		}
	}

	return 0;
}

double AntAlgorithm::calculateLikelihoodFactorOfChoosingVertex(int currentVertex, int candidateVertex, bool visited) {
	if (visited) return 0.0;
	if (currentVertex == candidateVertex) return 0.0;

	double eta = 1 / costGraph.getCost(currentVertex, candidateVertex);
	double tau = pheromoneConcentration[currentVertex][candidateVertex];

	return std::pow(tau, alpha) * std::pow(eta, beta);
}

std::vector<int> AntAlgorithm::findPath(std::vector<bool>& visited) {
	std::vector<int> path;
	double load = 0.0;
	int length = 0;
	int current = 0;

	while (true) {
		path.push_back(current);
		visited[current] = true;
		int next = chooseVertex(current, visited);
		if (load + demands[next] > capacity) break;
		if (length + 1 >= maxPathSize) break;

		load = load + demands[next];
		length++;
		
		current = next;
		if (current == 0) break;
	}

	path.push_back(0);
	return path;
}

std::vector<std::vector<int>> AntAlgorithm::findSolution() {
	std::vector<bool> visited(costGraph.verticesCount(), false);
	std::vector<std::vector<int>> solution;

	while (true) {
		auto path = findPath(visited);
		solution.push_back(path);

		bool allVisited = true;
		for (bool v : visited) {
			if (!v) {
				allVisited = false;
				break;
			}
		}

		if (allVisited) break;
	}

	return solution;
}

void AntAlgorithm::updatePheromoneOnPath(std::vector<int> path, double deltaPheromone)
{
	for (int i = 0; i < path.size() - 1; i++) {
		updatePheromone(path[i], path[i + 1], deltaPheromone);
	}
}

void AntAlgorithm::updatePheromone(int from, int to, double deltaPheromone) {
	pheromoneConcentration[from][to] +=  deltaPheromone;

}

void AntAlgorithm::evaporatePheromone() {
	for (int i = 0; i < pheromoneConcentration.size(); i++) {
		for (int j = 0; j < pheromoneConcentration.size(); j++) {
			pheromoneConcentration[i][j] *= (1 - pheromoneEvaporationCoefficient);
		}
	}
}

void AntAlgorithm::basicAntCvrp(double alpha, double beta, double pheromoneEvapotationCoefficient, int seed, int numberOfIterations) {

	this->alpha = alpha;
	this->beta = beta;
	this->pheromoneEvaporationCoefficient = pheromoneEvapotationCoefficient;
	double minCost = 9999999.99;

	const double startingValueOfPheromone = 1.0;
	const int graphSize = costGraph.verticesCount();

	pheromoneConcentration.resize(graphSize);
	for (int i = 0; i < graphSize; i++) {
		pheromoneConcentration[i].resize(graphSize);
		for (int j = 0; j < graphSize; j++) {
			pheromoneConcentration[i][j] = startingValueOfPheromone;
		}
	}
		
	randomGenerator.seed(seed);

	for (int iteration = 0; iteration < numberOfIterations; iteration++) {
		auto solution = findSolution();

		double cost = solutionCost(solution);
		double deltaPheromone = 100.0 / cost;
		for (auto path : solution)
			updatePheromoneOnPath(path, deltaPheromone);

		if (iteration % 20 == 0)
			evaporatePheromone();

		if (cost < minCost)
			minCost = cost;

		if(iteration % 100 == 0)
			std::cout << minCost << "\n";
		//checking solution correctness and cost
	}
}

double AntAlgorithm::solutionCost(std::vector<std::vector<int>> solution) {
	double cost = 0.0;

	for (auto path : solution) {
		for (int i = 0; i < path.size() - 1; i++) {
			cost += costGraph.getCost(path[i], path[i+1]);
		}
	}

	return cost;
}