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
	time = 0;

}
void Menu::displayMenu() 
{
	//HeldKarp hk(numberOfCities);
	while (x!=1)
	{
		system("cls");
		data();

		cout << "1. Wczytanie danych z pliku txt" << endl;
		cout << "2. Stworzenie danych" << endl;
		cout << "3. Wypisanie wczytanych danych" << endl;
		cout << "4. Wybor kryterium stopu [s]" << endl;
		cout << "5. Wybor temperatury poczatkowej" << endl;
		cout << "6. Algorytm - Symulowane wyzarzanie" << endl;
		cout << "7. Wyjscie" << endl;
		cin >> choice;
		switch (choice) {
			case 1:
			{
				system("cls");
				readFile();
				if(cities.size() != numberOfCities || numberOfCities <= 0) cout << "Dane nie zostaly wczytane" << endl;
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
				if (cities.size() == numberOfCities && numberOfCities > 0) cout << "Dane wczytane" << endl;
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
				cout << "Wpisz czas w sekundach: ";
				cin >> time;
				break;
			}
			case 5:
			{
				cout << "Wybierz temperature (wpisanie zera i wartosci mniejszych spowoduje przypisanie 1000): ";
				cin >> temperature;
				if (temperature <= 0) temperature = 1000;
				break;
			}
			case 6:
			{	
				if (cities.size() == numberOfCities || cities.size() != 0)
				{	
					SimulatedAnnealing sa(numberOfCities, cities);
					sa.temperature = temperature;
					sa.cities = cities;
					sa.numberOfCities = numberOfCities;
					sa.algorithm(time);
				}
				else 
					cout << "Najpierw wczytaj dane!" << endl;
				cout << endl;
				cout << "Nacisnij enter, aby kontynowac..." << endl;
				_getch();
				break;
			}
			case 7:
			{
				return;
				_getch();
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
	cout << "Daria Jezowska 252731 \nPEA Projekt 2 \n";
	if (numberOfCities > 0)
		cout << "Aktualny plik: " << fileName << endl;
	else
		cout << "Brak wczytanego pliku" << endl;
	cout << "Aktuanie ustawiona temperatura: " << temperature << endl;
	cout << "Aktualnie ustawiony czas: ";
	if (time == 0) cout << "brak ograniczenia czasowego\n" << endl;
	else cout << time << "[s]\n" << endl;
}
Menu::~Menu()
{
	cities.clear();
}
