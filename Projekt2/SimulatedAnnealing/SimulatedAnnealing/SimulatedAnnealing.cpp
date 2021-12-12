#include"SimulatedAnnealing.h"
SimulatedAnnealing::SimulatedAnnealing(int numberOfCities, vector<vector<int>> matrix)
{
	
	cities.clear();
	localBestPath.clear();
	this->numberOfCities = numberOfCities;

	//zmienne pomagajace w obliczniu minionego czasu
	
	start = 0;
	elapsed = 0;
	frequency = 0;
	
	//zmieniamy wektor na wektor dwuwymiarowy, ktory bedzie przechowywal polaczenia miedzy miastami
	cities.resize(numberOfCities, vector<int>(numberOfCities));

	//wektoryi zmienne odpowiadajace za sciezki i ich koszty
	localBestPath.resize(numberOfCities);
	globalBestPath.resize(numberOfCities);
	localBestPathCost = 0;
	globalBestPathCost = 0;
	prob = 0.0;
	iterations = numberOfCities * 10 ;
	
	delta = 0;
	double prob = 0;

	for (int i = 0; i < numberOfCities; i++)
	{
		for (int j = 0; j < numberOfCities; j++)
		{
			if (i == j)
			{
				cities[i][j] = INT_MAX;
				continue;
			}

			cities[i][j] = matrix[i][j];
		}
		
		localBestPath[i] = i;
		globalBestPath[i] = i;
	}
	elapsedMs = 0;
}

void SimulatedAnnealing::swapCities(vector<int>& path)
{
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, 10000);

	//zapobiegamy zmianie miasta poczatkowego losujac z zakresu o jeden mniejszego niz ilosc miast, a nastepnie dodajemy 1 
	//gdyby wylosowana liczba byla podzielna przez ilosc miast to zmianie ulegloby takze miasto startowe
	int x = (gen() % (numberOfCities - 1)) + 1;
	int y = (gen() % (numberOfCities - 1)) + 1;

	//jesli wylosujemy dwie takie same liczby to musimy wylosowac jedna z nich jeszcze raz
	while (x == y)
		x = (gen() % (numberOfCities - 1)) + 1;

	//zamiana miast miejscami
	int tmp = path[x];
	path[x] = path[y];
	path[y] = tmp;
	
}

long long int SimulatedAnnealing::read_QPC() // funkcja pomagajaca obliczyc nam czas
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

int SimulatedAnnealing::calculatePathCost(vector<int> path) // funkcja liczaca koszt sciezki
{
	int sum = 0;
	int x = 0, y = 0;
	
	//petla chodzi do rozmiaru sciezi - 1, aby przy ostatnim miescie nie wyszla poza zakres 
	//oraz abysmy mogli obliczyc koszt z ostatniego miasta do startowego
	for (int i = 0; i < path.size() - 1; i++)
	{
		x = path[i];
		y = path[i + 1];
		sum += cities[x][y];
	}
	x = path[numberOfCities - 1];
	y = path[0];
	sum += cities[x][y];

	return sum;
}

double SimulatedAnnealing::doubleRandom(double min, double max) // funkcja losujaca liczby z wybranego przedzialu
{
	return max + (rand() / (RAND_MAX / (min - max)));
}

void SimulatedAnnealing::randomPath(vector<int>& path) // funkcja mieszajaca cala sciezke za pomoca funkcji swapCities, ktora jest wyzej
{
	for (int i = 0; i < numberOfCities; i++)
	{
		swapCities(path);
	}
}

void SimulatedAnnealing::algorithm(int maxTime)
{
	maxTime *= 1000;
	if (maxTime == 0) maxTime = INT_MAX;

	//wektor i zmienna w ktorych bedziemy przechowywac sasiednia sciezke oraz jej koszt
	vector<int> nextPath(numberOfCities);
	int nextPathCost = 0;

	//losujemy sciezke i obliczamy jej koszt
	randomPath(localBestPath);
	localBestPathCost = calculatePathCost(localBestPath);

	//ustawiamy nasza najlepsza globalna sciezke na taka sama jak lokalna ciezka
	globalBestPath = localBestPath;
	globalBestPathCost = localBestPathCost;

	//ustawiamy sciezke sasiedzka na lokalnie najlepsza, aby moc pozniej ja modyfikowac w poszukiwaniu lepszej sciezki
	nextPath = localBestPath;

	//za pomoca start bedziemy obliczac czas, jaki minal
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	start = read_QPC();

	while(temperature > 0.0001 && maxTime > elapsedMs)
	{
		for (int i = 0; i < iterations; i++)
		{
			//jesli nie wejdziemy do zadnego if'a ponizej musimy zmienic nextPath na localBestPath, aby nie wejsc w nieoptymalne kombinacje sciezki
			nextPath = localBestPath;

			//zmieniamy kolejnosc dwoch miast
			swapCities(nextPath);

			//obliczamy koszt swiezo zmienionej sciezki
			nextPathCost = calculatePathCost(nextPath);

			//liczymy zmiane w kosztach sciezek
			delta = nextPathCost - localBestPathCost;

			//obliczamy prawdopodobienstwo 
			prob =  (double)exp((-1.0) * ((double)delta / (double)temperature));

			if(delta < 0) //jesli nowa, sasiedzka sciezka ma mniejszy koszt ustawiamy ja na globalnie najlepsza sciezke oraz na lokalnie najlepsza
			{
				globalBestPath = nextPath;
				globalBestPathCost = nextPathCost;
				localBestPathCost = nextPathCost;
				localBestPath = nextPath;
			}
			else if (doubleRandom(0, 1) < prob) 
			{
				// jesli koszt nowej sciezki jest wiekszy ale prawdopodobienstwo ma odpowiednia wartosc 
				//to ustawiamy nowa, sasiedzka sciezke jako lokalnie najlepsza
				//umozliwia nam to zaakceptowanie gorszego lokalnego rozwiazania w celu znalezienia globalnie najlepszego

				localBestPathCost = nextPathCost;
				localBestPath = nextPath;
			}
		}
		//zmniejszenie temperatury
		temperature *= coolingRate;
		//obliczenie czasu, ktory minal od rozpoczecia algorytmu
		elapsedMs = ((read_QPC() - start) * 1000.0) / frequency;
	}

	cout << endl;
	printPath();
	printCost();
	cout << "Czas [ms]: " << elapsedMs << " " << endl;
}
void SimulatedAnnealing::printCost() // wypisanie kosztu sciezki
{
	cout <<"Koszt: " << calculatePathCost(globalBestPath) << endl;
}

void SimulatedAnnealing::printPath() // wypisanie calej sciezki
{
	cout << "Sciezka: ";
	for (int i = 0; i < globalBestPath.size(); i++)
	{
		cout << globalBestPath[i] << " ";
	}
	cout << endl;
}
