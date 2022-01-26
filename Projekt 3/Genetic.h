#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <windows.h>
#include <stdlib.h>

using namespace std;

struct Population
{
	vector<int> path;
	int cost;
};

class GeneticAlgorithm {
public:
	int popultionSize;
	int numberOfCities;
	vector<vector<int>> cities;
	double mutationRate;
	double crossoverRate;
	int time;

	vector<Population> population;

	random_device rd;
	long long int start, elapsed, frequency;
	long long int elapsedMs;


	GeneticAlgorithm(vector<vector<int>> citiesMatrix, int populationSize, double mutationRate, double crossoverRate, int time);

	void mutation(Population& path, double mutationRate);
	Population crossoverOX(Population& first, Population& second);

	void countCost(Population& path);
	void generateRandomPath(Population& path);
	void shuffle(Population& path);
	void algorithm();
	vector<Population> nextGeneration(vector<Population> &population);
	bool compareCosts(Population &a, Population &b);
	void selectPopulation(vector<Population>& population);
	long long int read_QPC(); // funkcja pomagajaca obliczyc nam czas
	
};
