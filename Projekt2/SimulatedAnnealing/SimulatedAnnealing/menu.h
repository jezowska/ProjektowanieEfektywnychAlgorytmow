#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <ctime>
#include <random>
using namespace std;

class Menu {
public:
	//zmienne potrzebne do wczytywania danych z pliku
	int numberOfCities;
	vector<vector<int>> cities;
	bool isFileCorrectlyReaded;
	string fileName;
	fstream we;
	int time;
	int temperature = 1000;

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

