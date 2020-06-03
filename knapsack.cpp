// 0-1 knapsack problem
#include <iostream>
#include <iomanip>

struct TItem
{
	int weight = 0;
	int value = 0;
};

//DANE
constexpr int MAX_ITEMS = 5; //ilosc elementow
constexpr int SACK_CAP = 26; //pojemnosc plecaka + 1

void fillItems2(TItem item[MAX_ITEMS])
{
	item[0].weight = 14;
	item[0].value = 20;
	item[1].weight = 8;
	item[1].value = 5;
	item[2].weight = 3;
	item[2].value = 7;
	item[3].weight = 2;
	item[3].value = 1;
	item[4].weight = 10;
	item[4].value = 14;
}

void printP(int P[MAX_ITEMS][SACK_CAP])
{
	std::cout << std::endl;
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		for (int j = 0; j < SACK_CAP; j++)
			std::cout << std::setw(2) << P[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
	//std::system("pause");
}

void knapsack_dynamic(TItem items[MAX_ITEMS])
{
	int P[MAX_ITEMS][SACK_CAP];

	for (int i = 0; i < MAX_ITEMS; i++)
	{
		for (int j = 0; j < SACK_CAP; j++)
		{
			if (items[i].weight > j)
			{
				if (i == 0)
					P[i][j] = 0;
				else
					P[i][j] = P[i - 1][j];
			}
			else
			{
				int V1 = 0, V2 = 0;
				if (i == 0)
				{
					V1 = items[i].value;
					V2 = 0;
				}
				else
				{
					V1 = items[i].value + P[i - 1][j - items[i].weight];
					V2 = P[i - 1][j];
				}
				P[i][j] = (V1 > V2) ? V1 : V2;
			}
		}
	}

	std::cout << "Tablica pomocnicza: ";
	printP(P);
	std::cout << "Maksymalna wartosc sumaryczna w plecaku: " << P[MAX_ITEMS - 1][SACK_CAP - 1] << std::endl;
	std::cout << "Elementy w plecaku [waga,wartosc]: " << std::endl;

	int j = SACK_CAP - 1;
	for (int i = MAX_ITEMS - 1; i > -1; i--)
	{
		if (P[i][j] == 0) //doszlismy do konca, nie ma wiecej elementow
			break;
		if (P[i][j] == P[i - 1][j])//element nie jest w rozwiazaniu
		{
			continue;
		}
		else
		{ //element jest w rozwiazaniu
			std::cout << items[i].weight << "," << items[i].value << std::endl;
			j = j - items[i].weight; //w plecaku jest mniej miejsca o ten element
		}
	}
}

int knapsack_recursive(int i, int j, TItem items[MAX_ITEMS])
{
	if (i < 0 || j <= 0)
		return 0;
	if (items[i].weight > j)
		return knapsack_recursive(i - 1, j, items);
	else
	{
		int V1 = knapsack_recursive(i - 1, j - items[i].weight, items) + items[i].value;
		int V2 = knapsack_recursive(i - 1, j, items);
		return (V1 > V2) ? V1 : V2;
	}
}

int main1()
{
	TItem items[MAX_ITEMS];
	fillItems2(items);
	knapsack_dynamic(items);
	std::cout << std::endl << "Wartosc z rekursji: " << knapsack_recursive(MAX_ITEMS - 1, SACK_CAP - 1, items);
	return 0;
}
