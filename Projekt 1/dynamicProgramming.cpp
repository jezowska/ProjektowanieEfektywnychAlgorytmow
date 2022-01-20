#include "DynamicProgramming.h"
#include <algorithm>
DynamicProgramming::DynamicProgramming(vector<vector<int>> matrix, int size)
{
	if (size == 0 || matrix.empty())
	{
		cout << "Brak wczytanych danych!" << endl;
		exit(EXIT_FAILURE);
	}
	numberOfCities = size;	// zmienna przechowujaca ilosc miast
	cities.resize(numberOfCities, vector<int>(numberOfCities));	// wektor w ktorym zostana zapisane odleglosci miedzy danymi miastami
	cost = 0;	//koszt podrozy
	visitedCities = (1 << numberOfCities) - 1;  // po rozrysowaniu wszystkich mozliwych sciezek powstanie nam drzewo o liczbie wierzcholkow 2^(n) - 1
												// dlatego tworzymy zmienna visitedCities, ktora na kazdej pozycji bedzie miec jedynki i bedzie mozna porownac
												// np zapis 1101 bedzie oznaczac, ze odwiedzilismy miasta 3, 2 oraz 0
												// dlatego porownujac nasze do tej pory odwiedzone miasta z visitedCities bedziemy wiedziec czy wszystkie miasta zostaly odwiedzone
												// czy jednak ktores nam zostalo
	memo.resize((1 << numberOfCities), vector<int>(numberOfCities)); // dla wektora memo rezerwujemy 2^n miejsc w pamieci
	path.resize((1 << numberOfCities), vector<int>(numberOfCities)); // dla wektora memo rezerwujemy 2^n miejsc w pamieci
	p.resize(numberOfCities);

	//wczytanie danych 
	for (int i = 0; i < (1 << numberOfCities); i++)
	{
		for (int j = 0; j < numberOfCities; j++)
		{
			memo[i][j] = INT_MAX;
			//path[i][j] = INT_MAX;
			if (i < numberOfCities)
			{
				p[i] = INT_MAX;
				if (i == j)
					cities[i][j] = INT_MAX;
				else
					cities[i][j] = matrix[i][j];
			}
		}
	}
}
int DynamicProgramming::minCost(int cityToCheck, int visitedSoFar)
{
	int newMinCost = -1; 	//zmienna przechowujaca wartosc najmniejsza danego polaczenia
	//sprawdzamy czy wszystkie miasta zostaly odwiedzone
	if (visitedSoFar == visitedCities) 
	{
		//jesli zostaly odwiedzone to zwracamy droge z ostatniego miasta do miasta poczatkowego		
		return cities[cityToCheck][0];
	}
	if (memo[visitedSoFar][cityToCheck] != INT_MAX) 
	{
		//jeœli odwiedzilismy juz poszczegolne miasta i sa one zapamietane w naszej tablicy memo to zamiast od nowa przechodzic ta sciezke zwracamy ta wartosc
		return memo[visitedSoFar][cityToCheck];
	}
	

	for (int i = 0; i < numberOfCities; i++)
	{
		if (i == cityToCheck) continue;
		//sprawdzamy czy miasto i zosta³o ju¿ odwiedzone, jesli nie - mozemy dzialac dalej
		if ((visitedSoFar & (1 << i)) == 0)
		{
			/*sprawdzamy najkrotsza sciezke dla kazdego wierzcholka
			wywolujemy funkcje minCost rekurencyjnie - ilosc przypadkow, ktore mozemy rozwa¿ac jest 2^(n) - 1,
			wiêc zmienne visitedSoFar i visitedCities pomagaja nam poznac wszystkie mozliwe trasy i ich wartosci
			zapis visitedSoFar ! (1 << i) wywoluje minCost dla miast juz odwiedzonych zawierajacych nasze nowe miast i, po wyjsciu sprawdza czy by³a to najoptymalniejsza sciezka
			jesli byla - zmienna newMin przyjmuje wartosc actualCost
			*/
			int actualCost = cities[cityToCheck][i] + minCost(i, visitedSoFar | (1 << i));
			
			if (newMinCost == -1 || newMinCost > actualCost)
			{
				//w wektorze wektorow path przechowujemy nastepny wierzcholek
				//visitedSoFar mowi o odwiedzonych wierzcholkach, co pomoze nam pozniej odtworzyc cala sciezke, cityToCheck mowi o aktualnie przegladanym wierzcholku, a i o nastepnym
				newMinCost = actualCost;
				path[visitedSoFar][cityToCheck] = i;
			}
		}		
	}

	//po przejrzeniu wszystkich miast i znalezieniu najoptymalniejszej sciezki zwracamy funkcje newMin i wpisujemy ja do naszego wektora memo
	//if(cost > newMin) path.push_back(cityToCheck);

	memo[visitedSoFar][cityToCheck] = newMinCost;
	return newMinCost;
}

void DynamicProgramming::getPath(int start, int visited)
{
		//next mowi nam jaki nastepny wierzcholek mamy przeszukac w poszukiwaniu sciezki
		int next = path[visited][start];
		//w wektorze p przechowujemy nasza sciezke
		p[index] = next;
		cout << p[index] << " -> ";
		//na visited zaznaczamy, ze juz zaliczylismy miast nastepne i bedziemy mogli przejsc do jeszcze nastepnego w nastepnym wykonaniu petli
		visited = visited | (1 << next);

		if (index < p.size() - 1)
		{
			//naszym nowym wierzcholkiem do rozpatrywania bedzie next oraz zwiekszamy nasz index, tak aby moc pozniej zapisac sciezke
			index++;
			getPath(next, visited);
		}
		return;
	
}

void DynamicProgramming::doTSP() 
{
	cost = minCost(0, 1);
	displayCost();
}

void DynamicProgramming::displayCost() 
{
	cout << "Koszt: " <<  cost << endl;
	cout << "Sciezka: ";
	getPath(0, 0);
	cout << "0" << endl;
}

DynamicProgramming::~DynamicProgramming()
{
	memo.clear();
	cities.clear();
}