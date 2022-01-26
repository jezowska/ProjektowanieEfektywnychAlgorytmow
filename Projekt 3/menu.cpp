#include "menu.h"

Menu::Menu()
{
	choice = 0;
	cities.clear();
	numberOfCities = 0;
	fileName = "";
	isFileCorrectlyReaded = false;
	populationSize = 30;
	int x = 0;
	time = 10;

}
void Menu::displayMenu()
{
	while (x != 1)
	{
		system("cls");
		data();

		cout << "1. Wczytanie danych z pliku txt" << endl;
		cout << "2. Wybor kryterium stopu [s]" << endl;
		cout << "3. Wybor wspolczynnika krzyzowania" << endl;
		cout << "4. Wybor wspolczynnika mutacji" << endl;
		cout << "5. Wybor wielkosci populacji" << endl;
		cout << "6. Algorytm" << endl;
		cout << endl;
		cout << "7. Stworzenie danych" << endl;
		cout << "8. Wypisanie wczytanych danych" << endl;
		cout << "9. Wyjscie" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
		{
			system("cls");
			readFile();
			if (cities.size() != numberOfCities || numberOfCities <= 0) cout << "Dane nie zostaly wczytane" << endl;
			else
				cout << "Dane wczytane." << endl;

			cout << "Nacisnij enter, aby kontynowac..." << endl;
			_getch();
			break;
		}

		case 2:
		{
			cout << "Wpisz czas w sekundach: ";
			cin >> time;
			break;
		}
		case 3:
		{
			cout << "Wybierz wspolczynnik krzyzowania (wpisanie liczby innej niz z przedzialu 0-1 spowoduje przypisanie 0,01): ";
			cin >> crossoverRate;
			if (crossoverRate <= 0.0 || crossoverRate > 1.0) crossoverRate = 0.01;
			break;
		}

		case 4:
		{
			cout << "Wybierz wspolczynnik mutacji (wpisanie liczby innej niz z przedzialu 0-1 spowoduje przypisanie 0.01): ";
			cin >> mutationRate;
			if (mutationRate <= 0.0 || mutationRate > 1.0) crossoverRate = 0.01;
			break;
		}

		case 5:
		{
			cout << "Wpisz wielkoœæ populacji: ";
			cin >> populationSize;
			break;
		}
		case 6:
		{
			if (cities.empty())
			{
				cout << "Najpierw wczytaj dane!" << endl;
				cout << "Nacisnij enter, aby kontynowac." << endl;
				_getch();
				break;
			}
			else
			{
				GeneticAlgorithm ga(cities, populationSize, mutationRate, crossoverRate, time);
				ga.algorithm();
				cout << endl;
			}
				
			cout << endl;
			cout << "Nacisnij enter, aby kontynowac..." << endl;
			_getch();
			break;
		}

		case 7:
		{
			x = 1;
			break;
		}
		case 8:
		{
			system("cls");
			cout << "Podaj ilosc miast: " << endl;
			cin >> numberOfCities;
			generateRandom(numberOfCities);
			if (cities.size() == numberOfCities && numberOfCities > 0) cout << "Dane wczytane" << endl;
			else
				cout << "Dane nie zostaly wczytane" << endl;

			cout << "Nacisnij enter, aby kontynowac..." << endl;
			_getch();

			break;
		}
		case 9:
		{
			system("cls");

			if (cities.size() == numberOfCities) displayReadedData();

			cout << "Nacisnij enter, aby kontynowac..." << endl;
			_getch();
			break;
		}

		case 10:
		{
			cout << "Wybierz metode krzyzowania \n  1 - OX \n 2 - EX  ";
			cin >> crossoverType;
			while (crossoverType == 1 || crossoverType == 2)
			{
				cout << "Wpisz poprawn¹ wartoœæ!";
				cin >> crossoverType;
			}
			break;
		}
		case 11:
		{
			cout << "Wybierz metode mutacji \n  1 -  \n 2 - ";
			cin >> mutationType;
			while (mutationType != 1 || mutationType != 2)
			{
				cout << "Wpisz poprawn¹ wartoœæ!";
				cin >> mutationType;
			}
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
void Menu::readFile() //funkcja odpowiadajaca za wczytanie danych z pliku txt
{
	numberOfCities = 0;
	cities.clear();
	cout << "Podaj nazwe pliku txt (bez rozszerzenia): ";
	cin >> fileName;
	ifstream we;
	fileName.append(".txt");
	we.open(fileName);
	we >> numberOfCities;
	if (numberOfCities == 0) //jesli plik zostal zle wczytany wypisujemy blad
	{
		cout << "Bledny plik. ";
		return;
	}
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
void Menu::displayReadedData() //funkcja wyswietlajaca wczytane dane
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
void Menu::generateRandom(int size) //funkcja generujaca losowe dane do wektora o wybranym rozmiarze
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
void Menu::data() //funkcja wypisujaca aktualnie ustawione parametry
{
	cout << "Daria Jezowska 252731 \nPEA Projekt 3 \n";
	if (numberOfCities > 0)
		cout << "Aktualny plik: " << fileName << endl;
	else
		cout << "Brak wczytanego pliku" << endl;
	cout << "Wspolczynnik krzyzowania: " << crossoverRate << endl;
	cout << "Wspolczynnik mutowania: " << mutationRate << endl;
	cout << "Populacja: " << populationSize << endl;
	cout << "Czas: ";
	if (time == 0) cout << "brak ograniczenia czasowego\n" << endl;
	else cout << time << "[s]\n" << endl;
}
Menu::~Menu()
{
	cities.clear();
}
