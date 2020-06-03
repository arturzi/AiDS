#include <iostream>
#include <ctime>
#include <cstdlib>

constexpr int N = 10;

void generate_data(int arr[])
{
	bool gen = false;
	if (gen)
	{
		for (int i = 0; i < N; i++)
			arr[i] = std::rand() % 10;
	}
	else
	{
		arr[0] = 4;
		arr[1] = 6;
		arr[2] = 8;
		arr[3] = 2;
		arr[4] = 9;
		arr[5] = 5;
		arr[6] = 0;
		arr[7] = 3;
		arr[8] = 1;
		arr[9] = 7;
	}
}

void print_array(int arr[])
{
	for (int i = 0; i < N; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

void selection_sort(int arr[])
{
	if (N < 2)
		return;
	for (int i = 0; i < N - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < N; j++)
			if (arr[j] < arr[min])
				min = j;
		std::swap(arr[i], arr[min]);
	}
}

void insertion_sort(int arr[])
{
	for (int i = 1; i < N; i++)
	{
		int temp = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > temp)
			arr[j + 1] = arr[j--];
		arr[j + 1] = temp;
	}
}

void insertion_sort2(int arr[])
{
	for (int i = 1; i < N; i++)
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
			std::swap(arr[j - 1], arr[j]);
}

void bubble_sort(int arr[])
{
	for (int i = 0; i < N; i++)
	{
		bool swapped = false;
		for (int j = 0; j < N - 1; j++)
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		if (!swapped)
			return;
	}
}

int partition(int arr[], int a, int c)
{
	print_array(arr);
	int pivot = arr[c];
	int i = a - 1;
	for (int j = a; j < c; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;
			std::swap(arr[i], arr[j]);
		}
	}
	std::swap(arr[i + 1], arr[c]);
	return i + 1;
}

void quicksort(int arr[], int a, int c)
{
	int b = partition(arr, a, c);
	if (b - 1 > a)
		quicksort(arr, a, b - 1);
	if (b + 1 < c)
		quicksort(arr, b + 1, c);
}

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int arr[N];
	generate_data(arr);
	print_array(arr);
	//	selection_sort(arr);
	//	insertion_sort(arr);
	//bubble_sort(arr);
	quicksort(arr, 0, N - 1);
	print_array(arr);
	return 1;
}