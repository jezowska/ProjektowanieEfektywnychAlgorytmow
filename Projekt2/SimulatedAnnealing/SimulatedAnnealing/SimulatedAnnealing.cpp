#include"SimulatedAnnealing.h"

SA::SA(int numberOfCities, vector<vector<int>> matrix)
{
	cities.clear();
	currentPath.clear();
	this->numberOfCities = numberOfCities;

	random_device rd; 
	cities.resize(numberOfCities, vector<int>(numberOfCities));
	currentPath.resize(numberOfCities);
	currentCost = 0;

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
		
		currentPath[i] = i;
	}
	elapsedSec = 1;
}

void SA::printCost()
{
	cout << "Koszt: " << calculatePathCost(currentPath) << endl;
}

void SA::printPath()
{
	cout << "Sciezka: ";
	for (int i = 0; i < currentPath.size(); i++)
	{
		cout << currentPath[i] << " ";
	}
	cout << endl;
}

void SA::newPathSwap(vector<int>& path)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, 10000);
	//zapobiegamy zmianie miasta poczatkowego
	int x = (rand() % (numberOfCities - 1)) + 1;
	int y = (rand() % (numberOfCities - 1)) + 1;

	while (x == y)
		x = (rand() % (numberOfCities - 1)) + 1;

	//zamiana miejscami
	int tmp = path[x];
	path[x] = path[y];
	path[y] = tmp;
	
}

long long int SA::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

int SA::calculatePathCost(vector<int> path)
{
	int sum = 0;
	int x = 0, y = 0;
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

double SA::doubleRandom(double min, double max)
{
	double num = (double)rand() / RAND_MAX;
	return min + num * (max - min);
}

void SA::randomPath(vector<int>& path)
{
	shuffle(path.begin()+1, path.end(), default_random_engine(0));
}

vector<int> SA::algorithm(int maxTime)
{
	vector<int> nextPath(numberOfCities);
	int iterations = numberOfCities*numberOfCities;

	//randomPath(currentPath);
	currentCost = calculatePathCost(currentPath);

	nextPath = currentPath;
	int nextPathCost = calculatePathCost(nextPath);

	double prob = 0;

	start = read_QPC();

	while(temperature > 0.0001)
	{
		//cout << "elapsedTime" << elapsedSec << endl;
		//cout << "elapsed" << elapsed << endl;
		for (int i = 0; i < iterations; i++)
		{
			newPathSwap(nextPath);
			nextPathCost = calculatePathCost(nextPath);

			prob = -((nextPathCost - currentCost) / temperature);
			prob = (double)pow(e, prob);

			if((currentCost > nextPathCost) || (((double)rand() / (double)RAND_MAX) < prob))
			{
				
				currentCost = nextPathCost;
				currentPath = nextPath;
			}
		}
		
		temperature *= coolingRate;
		//elapsed = read_QPC() - start;
		//elapsedSec = (elapsedSec * 1000.0) / frequency;
	}
	
	return currentPath;
}
