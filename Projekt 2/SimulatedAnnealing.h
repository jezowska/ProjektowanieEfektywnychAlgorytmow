#pragma once
#include <iostream>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <ctime>
#include <windows.h>
#include <conio.h>

using namespace std;

class SimulatedAnnealing
{
public:
	const double coolingRate = 0.99;
	double temperature = 1000;
	double prob;
	int numberOfCities;
	int iterations;
	
	int delta;
	long long int start, elapsed, frequency;
	long long int elapsedMs;
	random_device rd;

	int bestPathCost;
	int localBestPathCost;
	int nextPathCost;
	int globalBestPathCost;
	vector<int> localBestPath;
	vector<int> globalBestPath;
	vector<vector<int>> cities;
	
	SimulatedAnnealing(int numberOfCities, vector<vector<int>> matrix);
	void swapCities(vector<int>& path);
	void algorithm(int maxTime);
	int calculatePathCost(vector<int> path);
	double doubleRandom(double min, double max);
	void randomPath(vector<int>& path);
	void printPath();
	void printCost();
	long long int read_QPC();
};