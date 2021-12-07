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

class SA
{
public:
	const double coolingRate = 0.99;
	double temperature = 500;
	double prob;
	int numberOfCities;
	int iterations;
	
	int change;
	long long int start, elapsed, frequency;
	long long int elapsedMs;
	
	int bestPathCost;
	int currentCost;
	int nextPathCost;
	int bestCost;
	vector<int> currentPath;
	vector<int> bestPath;
	vector<vector<int>> cities;
	
	SA(int numberOfCities, vector<vector<int>> matrix);
	void swapCities(vector<int>& path);
	vector<int> algorithm(int maxTime);
	int calculatePathCost(vector<int> path);
	double doubleRandom(double min, double max);
	void randomPath(vector<int>& path);
	void printPath();
	void printCost();
	long long int read_QPC();
};