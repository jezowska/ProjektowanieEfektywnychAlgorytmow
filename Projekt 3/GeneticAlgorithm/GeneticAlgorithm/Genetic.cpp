#include "Genetic.h"

GeneticAlgorithm::GeneticAlgorithm(vector<vector<int>> citiesMatrix, int populationSize,double mutationRate, double crossoverRate, int time)
{
	cities = citiesMatrix;
	numberOfCities = cities[0].size();
	this->popultionSize = populationSize;
	this->mutationRate = mutationRate;
	this->crossoverRate = crossoverRate;
	this->time = time; 
}

void GeneticAlgorithm::mutation(Population& path, double mutationRate)
{
	mt19937 gen(rd());

	//funkcja mutuj�c, losuj�ca dwa miasta oraz zamieniaj�ca je miejscami

	int x = 0;
	int y = 0;

	while (x == y)
	{
		x = (gen() % (path.path.size() - 1)) + 1;
		y = (gen() % (path.path.size() - 1)) + 1;
	}

	int tmp = path.path[x];
	path.path[x] = path.path[y];
	path.path[y] = tmp;
	countCost(path);
}

Population GeneticAlgorithm::crossoverOX(Population& first, Population& second)
{
	Population child;
	mt19937 gen(rd());


	// ustalenie rozmiaru �cie�ki potomka
	child.path.resize(first.path.size());

	int x = gen() % (first.path.size() - 1) + 1;
	int y = gen() % (first.path.size() - 1) + 1;

	while (x == y)
	{
		x = gen() % (first.path.size() - 1) + 1;
		y = gen() % (first.path.size() - 1) + 1;
	}
	//do poprawnego krzy�owania x musi by� mniejsze ni� y 
	if (x > y)
	{
		int tmp = x;
		x = y;
		y = tmp;
	}
	
	//miasta z wylosowanego przedzia�u <x,y> s� przenoszone do dziecka, tak�e na tych samych pozycjach
	for (int i = x; i <= y; i++)
	{
		child.path[i] = first.path[i];
	}
	//zmienna tmp pomo�e w przypisywaniu potomkowi cech drugiego rodzica
	int tmp = 1;
	for (int i = 1; i < second.path.size(); i++)
	{
		
		bool skip = false;

		for (int j = 1; j < second.path.size(); j++)
		{
			if (second.path[i] == child.path[j] && child.path[j] != 0)
			{
				//je�li dane miasto drugiego rodzica znajduje si� w dziecku, zmienna skip zmienia si� na true
				skip = true;
				break;
			}
		}

		//je�li dane miasto z drugiego rodzica jeszcze nie wyst�pi�o w dziecku to je przypisujemy dla pierwszej wolnej pozycji, o kt�rej m�wi tmp
		if (skip == false)
		{
			if (tmp >= x && tmp <= y) tmp = y + 1;
			child.path[tmp] = second.path[i];
			tmp++;
		}
	}
	//na samym ko�cu obliczamy warto�� �cie�ki dziecka
	countCost(child);
	return child;
}

void GeneticAlgorithm::countCost(Population& path)
{
	int cost = 0;
	int x = 0, y = 0;

	//petla chodzi do rozmiaru sciezi - 1, aby przy ostatnim miejscu nie wyszla poza zakres 
	//oraz abysmy mogli obliczyc koszt z ostatniego miasta do startowego
	for (int i = 0; i < path.path.size() - 1; i++)
	{
		x = path.path[i];
		y = path.path[i + 1];
		cost += cities[x][y];
	}
	x = path.path[path.path.size() - 1];
	y = path.path[0];
	cost += cities[x][y];

	path.cost = cost;
}

void GeneticAlgorithm::generateRandomPath(Population& path)
{
	//stworzenie �cie�ki, a nast�pnie jej wymieszanie
	for (int i = 0; i < cities[0].size(); i++)
	{
		path.path.push_back(i);
	}
	shuffle(path);
	countCost(path);
}

void GeneticAlgorithm::shuffle(Population& path)
{
	mt19937 gen(rd());

	//funkcja shuffle losuje dwie liczby z przedzia�u 1-(liczba miast), a nast�pnie zamienia te miasta miejscami ze sob�
	for (int i = 0; i < path.path.size(); i++)
	{
		int x = (gen() % (numberOfCities - 1)) + 1;
		int y = (gen() % (numberOfCities - 1)) + 1;
		 
		//p�tla zapobiegaj�ca wyolosowanie dw�ch takich samych liczb
		while (x == y)
			x = (gen() % (numberOfCities - 1)) + 1;

		//zamiana miast miejscami
		int tmp = path.path[x];
		path.path[x] = path.path[y];
		path.path[y] = tmp;
	}

	countCost(path);
}

void GeneticAlgorithm::selectPopulation(vector<Population>& population)
{
	//funkcja sort z trzema argumentami sortuje dany zakres pod pewnymi warunkami - w tym wypadku sortuje od najmniejszgo kosztu �cie�ki do najwi�kszeog
	std::sort(population.begin(), population.end(), [](const Population& a, const Population& b) {return a.cost < b.cost; });
	if (popultionSize < population.size()) {
		for (int i = 0; i < population.size() - popultionSize; i++)
		{
			//nast�pnie, je�li ilo�� osobnik�w w populacji przekracza za�o�on� z g�ry liczb� osobnik�w to cz�� z nich, o najwi�kszych kosztach jest usuwana
			population.pop_back();
		}
	}
}

void GeneticAlgorithm::algorithm()
{
	Population path;
	population.resize(popultionSize);
	generateRandomPath(path);
	population[0] = path;

	mt19937 gen(rd());
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	start = read_QPC();
	
	if (popultionSize % 2 != 0)
	{
		cout << "Populacja powinna by� parzysta!" << endl;
		return;
	}

	//stworzenie odpowiedniej ilo�ci osobnik�w oraz doadnie ich na wektor population
	for (int i = 0; i < popultionSize; i++)
	{		
		shuffle(path);
		population[i] = path;
	}

	while ((time*1000) > elapsed)
	{
		
		int popSize = (int)population.size();

		Population firstChild;
		Population secondChild;
	
		//p�tla for chodzi o rozmiar populacji -1, aby wywo�anie funkcji krzy�owania mog�o zaj�� i nie wykroczy�o poza zakres wektora population
		for (int i = 0; i < popSize - 1; i++)
		{
			Population child;
			mt19937 gen(rd());



			double random = rand();
			random = random / RAND_MAX;

			if (crossoverRate > random)
			{
				int x = gen() % popultionSize;
				int y = gen() % popultionSize;
				while (x == y)
				{
					x = gen() % popultionSize;
					y = gen() % popultionSize;
				}

				firstChild = crossoverOX(population[x], population[y]);
				secondChild = crossoverOX(population[y], population[x]);
				population.push_back(firstChild);
				population.push_back(secondChild);
			}
		}
		
		for (int i = 0; i < (int) population.size(); i++)
		{
			int x = gen() % popultionSize;
			double random = rand();
			random = random / RAND_MAX;
			if (mutationRate > random)
			{
				mutation(population[x], mutationRate);
			}
		}
		//selekcja populacji
		selectPopulation(population);
		elapsed = ((read_QPC() - start) * 1000.0) / frequency;
	}
	cout << " \nCzas: " << elapsed / 1000.0 << " s " << endl;
	cout << "Koszt: " << population[0].cost << endl;
	cout << "Sciezka: ";
	for (int i = 0; i < population[0].path.size(); i++)
	{
		cout << population[0].path[i] << " ";
	}
}

long long int GeneticAlgorithm::read_QPC() // funkcja pomagajaca obliczyc nam czas
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

