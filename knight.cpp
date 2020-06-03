#include <iostream>
#include <iomanip>

constexpr int N = 6;

struct TKnight
{
	bool visited = false;
	int move = 0;
};

void display(TKnight tk[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			std::cout << std::setw(2) << tk[i][j].move << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void knights_tour(int x, int y, int mov, TKnight tk[N][N])
{
	tk[x][y].visited = true;
	tk[x][y].move = mov;

	if (mov >= N * N)
	{
		std::cout << "DONE!!!" << std::endl;
		display(tk);
		std::exit(1);
	}

	int a = 0, b = 0;
	//move 1
	a = x - 2;
	b = y - 1;
	if (a < N && a >= 0 && b < N && b >= 0 && !tk[a][b].visited)
		knights_tour(a, b, mov + 1, tk);
	//move 2
	a = x - 1;
	b = y - 2;
	if (a < N && a >= 0 && b < N && b >= 0 && !tk[a][b].visited)
		knights_tour(a, b, mov + 1, tk);
	//move 3
	a = x + 1;
	b = y - 2;
	if (a < N && a >= 0 && b < N && b >= 0 && !tk[a][b].visited)
		knights_tour(a, b, mov + 1, tk);
	//move 4
	a = x + 2;
	b = y - 1;
	if (a < N && a >= 0 && b < N && b >= 0 && !tk[a][b].visited)
		knights_tour(a, b, mov + 1, tk);
	//move 5
	a = x + 2;
	b = y + 1;
	if (a < N && a >= 0 && b < N && b >= 0 && !tk[a][b].visited)
		knights_tour(a, b, mov + 1, tk);
	//move 6
	a = x + 1;
	b = y + 2;
	if (a < N && a >= 0 && b < N && b >= 0 && !tk[a][b].visited)
		knights_tour(a, b, mov + 1, tk);
	//move 7
	a = x - 1;
	b = y + 2;
	if (a < N && a >= 0 && b < N && b >= 0 && !tk[a][b].visited)
		knights_tour(a, b, mov + 1, tk);
	//move 8
	a = x - 2;
	b = y + 1;
	if (a < N && a >= 0 && b < N && b >= 0 && !tk[a][b].visited)
		knights_tour(a, b, mov + 1, tk);

	tk[x][y].visited = false;
	tk[x][y].move = 0;
}

int main2()
{
	TKnight tk[N][N];
	knights_tour(2, 2, 1, tk);
	display(tk);
	return 0;
}