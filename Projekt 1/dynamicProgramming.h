#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <windows.h>
#include <ctime>
#include <fstream>

using namespace std;
class DynamicProgramming
{
public:
	vector<vector<int>> cities;
	int numberOfCities;
	int cost;
	int visitedCities;
	vector<vector<int>> memo;
	vector<vector<int>> path;
	vector<int> p;
	int index;

	int minCost(int cityToCheck, int visitedSoFar);
	void doTSP();
	void displayCost();
	DynamicProgramming(vector<vector<int>> matrix, int size);
	~DynamicProgramming();
	void getPath(int start, int visited);

};