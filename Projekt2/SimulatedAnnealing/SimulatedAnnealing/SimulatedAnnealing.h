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
	double temperature = 10000;
	const double e = 2.718281828459;
	int numberOfCities;
	long long int start, elapsed, frequency;
	double elapsedSec;
	
	int bestPathCost;
	int currentCost;
	vector<int> bestPath;
	vector<int> currentPath;
	vector<vector<int>> cities;
	

	SA(int numberOfCities, vector<vector<int>> matrix);
	void newPathSwap(vector<int>& path);
	float randomFloat(int min, int max);
	vector<int> algorithm(int maxTime);
	int calculatePathCost(vector<int> path);
	double doubleRandom(double min, double max);
	void randomPath(vector<int>& path);
	void printPath();
	void printCost();
	long long int read_QPC();

};