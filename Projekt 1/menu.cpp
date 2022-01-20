#include "menu.h"
#include "dynamicProgramming.h"

Menu::Menu()
{
	choice = 0;
	cities.clear();
	numberOfCities = 0;
	fileName = "";
	isFileCorrectlyReaded = false;
	int x = 0;
	

}
void Menu::displayMenu() 
{
	//HeldKarp hk(numberOfCities);
	while (x!=1)
	{
		system("cls");
		cout << "1. Wczytanie danych z pliku txt" << endl;
		cout << "2. Programowanie dynamiczne" << endl;
		cout << "3. Generowanie danych losowych" << endl;
		cout << "4. Wyswietlenie wczytanych danych" << endl;
		cout << "5. Testy czasowe" << endl;
		cout << "6. Wyjscie" << endl;
		cin >> choice;
		switch (choice) {
			case 1: {
				system("cls");
				readFile();

				break;
			}
			case 2:
			{
				QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
				system("cls");
				DynamicProgramming dp(cities, numberOfCities);
				start = read_QPC();
				dp.doTSP();
				elapsed = read_QPC() - start;
				dp.displayCost();
				cout << "Czas: " << (1000.0 * elapsed) / frequency << "ms" << endl;
				cout << "Nacisnij enter, aby kontynowac..." << endl;
				_getch();
				break;
			}
			case 3:
			{
				cout << "Podaj ilosc miast: ";
				int size;
				cin >> size;
				system("cls");
				generateRandom(size);
				break;

			}
			case 4:
			{
				system("cls");
				displayReadedData();
				cout << endl;
				cout << "Nacisnij enter, aby kontynowac..." << endl;
				_getch();
				break;
			}
			case 5:
			{
				int numOfTest, numOfCities;

				cout << "Dla ilu zestawow miast maja zostac wykonane testy? ";
				cin >> numOfTest;
				cout << "Po ile miast ma byc w kazdym zestawie? " << endl;
				cin >> numOfCities;

				for (int i = 0; i < numOfTest; i++)
				{
					QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
					cout << "Zestaw nr " << i << ":" << endl;
					generateRandom(numOfCities);
					DynamicProgramming dp(cities, numberOfCities);
					start = read_QPC();
					dp.doTSP();
					elapsed = read_QPC() - start;
					dp.displayCost();
					 
					cout << "Czas: " << (1000.0 * elapsed) / frequency << "ms" << endl;
				}
				_getch();
				break;
			}
			case 6:
			{
				system("cls");
				x = 1;
				break;
			}
			default:
			{
				cout << "Niepoprawny wybór. Nacisnij enter, aby wybrac ponownie." << endl;
				_getch();
				break;
			}
		}
	}
}
void Menu::readFile()
{
	numberOfCities = 0;
	cities.clear();
	cout << "Podaj nazwê pliku txt (bez rozszerzenia): ";
	cin >> fileName;
	ifstream we;
	fileName.append(".txt");
	we.open(fileName);
	we >> numberOfCities;
	cout << numberOfCities << endl;
	cities.resize(numberOfCities, vector<int>(numberOfCities));

	for (unsigned int i = 0; i < cities.size(); i++)
	{
		cities[i].resize(numberOfCities);
		for (unsigned int j = 0; j < cities[i].size(); j++)
		{
			if (we)
				we >> cities[i][j];
		}
	}
}
void Menu::displayReadedData()
{
	if (numberOfCities == 0)
	{
		cout << "Brak wczytanych danych" << endl;
		return;
	}
	for (int i = 0; i < numberOfCities; i++)
	{
		for (int j = 0; j < numberOfCities; j++)
		{
			cout << cities[i][j] << " ";
		}
		cout << endl;
	}
}

void Menu::generateRandom(int size)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, 1000000);
	numberOfCities = size;

	cities.clear();
	cities.resize(size, vector<int>(size));

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{

			if (i == j)
			{
				cities[i][j] = INT_MAX;
				continue;
			}
			cities[i][j] = dist(gen);
		}
	}
}
Menu::~Menu()
{
	cities.clear();
}
