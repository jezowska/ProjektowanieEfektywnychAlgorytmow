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
	prob = 0.0;
	iterations = numberOfCities * 10;
	nextPathCost = 0;
	
	change = 0;
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
		
		currentPath[i] = i;
	}
	elapsedMs = 0;
}

void SA::printCost()
{
	cout <</* "Koszt: " <<*/ calculatePathCost(currentPath) << endl;
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

void SA::swapCities(vector<int>& path)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, 10000);
	//zapobiegamy zmianie miasta poczatkowego
	int x = (gen() % (numberOfCities - 1)) + 1;
	int y = (gen() % (numberOfCities - 1)) + 1;

	while (x == y)
		x = (gen() % (numberOfCities - 1)) + 1;

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
	return max + (rand() / (RAND_MAX / (min - max)));
}

void SA::randomPath(vector<int>& path)
{
	for (int i = 0; i < numberOfCities; i++)
	{
		swapCities(path);
	}

	//shuffle(path.begin()+1, path.end(), default_random_engine(0));
}

vector<int> SA::algorithm(int maxTime)
{
	if (maxTime == 0) maxTime = INT_MAX;
	vector<int> nextPath(numberOfCities);

	randomPath(currentPath);
	currentCost = calculatePathCost(currentPath);

	bestPath = currentPath;
	bestCost = currentCost;

	nextPath = currentPath;
	elapsedMs = 1;

	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	start = read_QPC();

	while(temperature > 0.0001 && maxTime > elapsedMs)
	{
		temperature *= coolingRate;
		for (int i = 0; i < iterations; i++)
		{
			nextPath = currentPath;

			swapCities(nextPath);

			nextPathCost = calculatePathCost(nextPath);

			change = nextPathCost - currentCost;

			prob =  (double)exp((-1.0) * ((double)change / (double)temperature));

			if(change < 0)
			{
				bestPath = nextPath;
				bestPathCost = nextPathCost;
				currentCost = nextPathCost;
				currentPath = nextPath;
			}
			else if (doubleRandom(0, 1) < prob)
			{
				currentCost = nextPathCost;
				currentPath = nextPath;
			}
		}
		
		elapsedMs = ((read_QPC() - start) * 1000.0) / frequency;
	}
	currentPath = bestPath;
	//cout << endl;
	//cout /* << "Czas [ms]: "*/ << elapsedMs <<" " ;
	return currentPath;
}
