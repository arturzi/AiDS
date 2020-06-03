//Zadanie p2
//Artur Zieliński 165095
#include <iostream>
#include <string>
#include <fstream>

struct TTowar
{
	std::string nazwa;
	double waga = 0;
	double cena = 0;
	TTowar* next = nullptr;
};

//wykorzystując funkcję Wypisz, która drukuje
//z jakimś nagłówkiem zawartość listy zaczynającej się pod jakimś adresem.
void Wypisz(TTowar* head, std::string header = "")
{
	if (!header.empty()) //jesli jest naglowek - drukujemy
		std::cout << std::endl << header << std::endl;
	if (head == nullptr) //nie ma co drukowac
		return;
	std::cout << head->nazwa << "\t" << head->waga << "\t" << head->cena << std::endl;
	Wypisz(head->next);
}

TTowar* Towary(TTowar* &head, double weight, double price, bool& removed)
{
	//Napisać funkcję Towary, która dla listy jednokierunkowej artykułów spożywczych zawierającej
	//dane(nazwa, waga, cena) i zaczynającej się pod jakimś adresem :
	//1. usuwa z listy pierwsze dwa artykuły o cenie większej od jakiejś wartości i wadze większej od
	//jakiejś wartości
	if (head == nullptr) //lista jest pusta
	{
		removed = false;
		return nullptr;
	}

	int removed_count = 0;//ile elementow usunieto
	double total_weight = 0, total_price = 0;//calkowite wartosci dla liczenia sredniej
	int element_count = 0;//ilosc elementow do liczenia sredniej

	TTowar* tmp = head;//aktualny element podczas iteracji
	TTowar* prev = head;//poprzedni element podczas iteracji
	while (tmp != nullptr)
	{
		if (tmp->cena > price && tmp->waga > weight && removed_count < 2)//powinnismy skasowac element
		{
			if (tmp == head)//usuwanie pierwszego elementu, trzeba dodatkowo przesunac wskaźnik wejsciowy
			{
				if(head->next == nullptr)
				{
					//uh.. zostal juz tylko jeden element, lista bedzie pusta
					delete head;
					removed_count++;
					head = nullptr;
					break;
				}
				head = head->next;
				delete tmp;
				removed_count++;
				tmp = head;
				prev = head;
			}
			else//usuwanie kazdego innego elementu niz pierwszy
			{
				prev->next = tmp->next;
				delete tmp;
				removed_count++;
				tmp = prev->next;
				//poprzedni element sie nie zmienia, wiec prev bez zmian
			}
		}
		else //skoro nie usuwamy to zliczamy do sredniej
		{
			element_count++;
			total_weight += tmp->waga;
			total_price += tmp->cena;
			prev = tmp;
			tmp = tmp->next;
		}
	}
	//oraz przekazuje przez parametr informację logiczną, czy udało się znaleźć i
	//usunąć dwa takie artykuły
	removed = (removed_count > 1) ? true : false;

	Wypisz(head, "Zawartosc listy po usunieciu 2 artykulow:\n[Nazwa\tWaga\tCena]");

	//2. dopisuje - jako ostatni – artykuł o nazwie „Sredni” posiadający średnią cenę i średnią wagę
	//będących na liście artykułów
	TTowar* averages = new TTowar;
	averages->nazwa = "Sredni";
	if (element_count > 0)
	{
		averages->cena = total_price / element_count;
		averages->waga = total_weight / element_count;
	}
	averages->next = nullptr;

	//tutaj robie dodatkowe  zalozenie, ze jezeli na liscie nie zostal zaden artykul, to nie
	//dopisuje elementu ze srednimi
	//jesli ma byc inaczej to jaka wtedy ma byc ta srednia? nie moze byc np. zerem, bo zero to tez
	//istotna wartosc dla np. Ceny
	if (head != nullptr)
		prev->next = averages;//po zakonczeniu iteracji listy tutaj bedzie ostatni element

	Wypisz(head, "Zawartosc listy ze srednimi na koncu:\n[Nazwa\tWaga\tCena]");

	//ponownie jesli nie ma elementow, nie ma srednich
	return (head) ? averages : nullptr;
}

int main()
{
	//Funkcję Towary wykorzystać w programie, który:
	//a.tworzy listę wczytując dane z pliku o nazwie podanej przez użytkownika
	std::cout << "Podaj nazwe pliku: ";
	std::string fname = "";
	std::cin >> fname;

	std::cout << "Podaj cene: ";
	double price = 0;
	std::cin >> price;

	std::cout << "Podaj wage: ";
	double weight = 0;
	std::cin >> weight;

	std::ifstream file_in(fname);
	if (!file_in.is_open())
	{
		std::cout << "Nie znaleziono pliku " << fname;
		std::exit(0);
	}

	TTowar* head = nullptr, *tmp = nullptr;
	while (!file_in.eof())
	{
		TTowar* elem = new TTowar;
		file_in >> elem->nazwa;
		file_in >> elem->waga;
		file_in >> elem->cena;
		elem->next = nullptr;

		if (head == nullptr) //pierwszy element
		{
			head = elem;
			tmp = head;
		}
		else
		{
			tmp->next = elem;
			tmp = elem;
		}
	}
	Wypisz(head, "Zawartosc listy po wczytaniu:\n[Nazwa\tWaga\tCena]");

	//b. wywołuje funkcję Towary dla utworzonej listy na parametrach aktualnych wczytanych z
	//klawiatury
	bool removed = false;
	TTowar* info = Towary(head, weight, price, removed);

	//c.drukuje informację, czy z listy usunięto dwa artykuły
	if (removed)
		std::cout << std::endl << "Z listy usunieto dwa artykuly." << std::endl;
	else
		std::cout << std::endl << "Z listy nie usunieto dwoch artykulow." << std::endl;

	//d. zwraca średnią cenę i średnią wagę artykułów korzystając z adresu ostatniego elementu listy,
	//wyznaczonego przez funkcję Towary.
	
	//hmm poprzez zwraca chyba chodzi o drukuje? main nie moze nic sensownego zwrocic
	if (info != nullptr)
	{
		std::cout << "Srednia cena: " << info->cena << std::endl;
		std::cout << "Srednia waga: " << info->waga << std::endl;
	}

	//e.kasuje utworzoną listę.
	while (head != nullptr)
	{
		tmp = head;
		head = head->next;
		delete tmp;
	}
}

/*

Napisać funkcję Towary, która dla listy jednokierunkowej artykułów spożywczych zawierającej
dane (nazwa, waga, cena) i zaczynającej się pod jakimś adresem:
1. usuwa z listy pierwsze dwa artykuły o cenie większej od jakiejś wartości i wadze większej od
jakiejś wartości oraz przekazuje przez parametr informację logiczną, czy udało się znaleźć i
usunąć dwa takie artykuły
2. dopisuje - jako ostatni – artykuł o nazwie „Sredni” posiadający średnią cenę i średnią wagę
będących na liście artykułów
3. zwraca adres tego ostatniego artykułu
4. po każdej z powyższych operacji drukuje listę, wykorzystując funkcję Wypisz, która drukuje
z jakimś nagłówkiem zawartość listy zaczynającej się pod jakimś adresem.
Funkcję Towary wykorzystać w programie, który:
a. tworzy listę wczytując dane z pliku o nazwie podanej przez użytkownika
b. wywołuje funkcję Towary dla utworzonej listy na parametrach aktualnych wczytanych z
klawiatury
c. drukuje informację, czy z listy usunięto dwa artykuły
d. zwraca średnią cenę i średnią wagę artykułów korzystając z adresu ostatniego elementu listy,
wyznaczonego przez funkcję Towary.
e. kasuje utworzoną listę.
Funkcję poprzedzić definicją odpowiedniej struktury. Uwaga: słowo jakiś oznacza parametr
funkcji.
UWAGA: w programie należy zdefiniować i wykorzystać tylko dwie funkcje: Towary i Wypisz.

*/

//plik do testow:
/*
cebula
0.5
12.98
Olej
1
6.98
Czosnek
1
1.49
Papryka
0.08
74.75
Cukier
1
2.48
Orzechy
1
9.80
*/