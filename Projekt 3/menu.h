#pragma once
#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <ctime>
#include <random>
#include "Genetic.h"
using namespace std;

class Menu {
public:
	//zmienne potrzebne do wczytywania danych z pliku
	int numberOfCities;
	vector<vector<int>> cities;
	bool isFileCorrectlyReaded;
	string fileName;
	fstream we;
	int time = 10;
	double crossoverRate = 0.8;
	int crossoverType = 0;
	double mutationRate = 0.01;
	int mutationType = 0;
	int populationSize;

	int x;
	long long int frequency, start, elapsed;


	//zmienne potrzebne do wyœwietlania menu
	int choice;

	Menu();
	~Menu();

	void displayMenu();
	void readFile();
	void displayReadedData();
	void generateRandom(int size);
	void data();
	long long int read_QPC()
	{
		LARGE_INTEGER count;
		QueryPerformanceCounter(&count);
		return((long long int)count.QuadPart);
	}
};

