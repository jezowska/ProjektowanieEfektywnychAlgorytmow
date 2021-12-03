#include "menu.h"
#include "SimulatedAnnealing.h"

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
		cout << "2. Stworzenie danych" << endl;
		cout << "3. Wypisanie wczytanych danych" << endl;
		cout << "4. Algorytm - Symulowane wyzarzanie" << endl;
		cout << "6. Wyjscie" << endl;
		cin >> choice;
		switch (choice) {
			case 1:
			{
				system("cls");
				readFile();
				if(cities.size() != numberOfCities) cout << "Niepoprawna nazwa pliku! Dane nie zostaly wczytane" << endl;
				else 
					cout << "Dane wczytane." << endl;

				cout << "Nacisnij enter, aby kontynowac..." << endl;
				_getch();
				break;
			}
			case 2:
			{
				system("cls");
				cout << "Podaj ilosc miast: " << endl;
				cin >> numberOfCities;
				generateRandom(numberOfCities);
				if (cities.size() == numberOfCities) cout << "Dane wczytane" << endl;
				else 
					cout << "Dane nie zostaly wczytane" << endl;

				cout << "Nacisnij enter, aby kontynowac..." << endl;
				_getch();

				break;
			}
			case 3:
			{
				system("cls");

				if(cities.size() == numberOfCities) displayReadedData();

				cout << "Nacisnij enter, aby kontynowac..." << endl;
				_getch();
				break;
			}
			case 4:
			{	
				if (cities.size() == numberOfCities)
				{
					SA sa(numberOfCities, cities);
					sa.algorithm(numberOfCities*numberOfCities);
					sa.printPath();
					sa.printCost();
				}
				else 
					cout << "Najpierw wczytaj dane!" << endl;

				
				cout << "Nacisnij enter, aby kontynowac..." << endl;
				_getch();
				break;
			}
			case 5:
			{
				_getch();
				break;
			}
			case 6:
			{
				system("cls");
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
