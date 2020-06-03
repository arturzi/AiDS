//Zadanie p1
//Artur Zieliński 165095

#include <iostream>
#include <string>

struct TTowar
{
	std::string nazwa;
	double cena = 0;
	TTowar* next = nullptr;
};

void append(TTowar* &head, TTowar* element)
{
	if (element == nullptr)
		return; //nie ma co wstawiać

	//najpierw trzeba znalezc ostatni element
	if (head == nullptr) //moze to byc pierwszy element, jesli lista jest pusta
	{
		head = element;
	}
	else
	{
		TTowar* tmp = head; //potrzebny lokalny wskaźnik bo jesli ruszymy list to zgubimy *head w main()
		while (tmp->next != nullptr) //iterujemy na koniec listy
			tmp = tmp->next;
		//i łączymy
		tmp->next = element;
	}
}

void display(TTowar* head)
{
	if (head == nullptr)
		return;
	std::cout << head->nazwa << "\t" << head->cena << std::endl;
	display(head->next);
}

void deletelist(TTowar* & head)//tak jest chyba poprawnie, inaczej musielibysmy dodatkowo skasowac *head w main()
{
	//najpierw sprawdzamy, czy jest co kasowac
	if (head == nullptr)
		return;

	//i kasujemy po kolei kazdy poprzedni element
	TTowar* tmp = nullptr;
	while (head != nullptr)
	{
		tmp = head;
		head = head->next;
		delete tmp;
	}
	head = nullptr;
}

int main()
{
	//1. Wczytać z klawiatury dane dotyczące pięciu produktów (nazwa, cena) i utworzyć z nich listę
	//	jednokierunkową w kolejności zgodnej z wczytywaniem, wykorzystując funkcję, która dopisuje towar
	//		o jakichś danych na końcu listy zaczynającej się pod jakimś adresem.
	TTowar* head = nullptr;
	for (int i = 1; i < 6; i++)
	{
		TTowar* elem = new TTowar;
		elem->cena = 0;
		elem->nazwa = "";
		elem->next = nullptr;
		std::cout << "Element " << i << " nazwa (string): ";
		std::cin >> elem->nazwa;
		std::cout << "Element " << i << " cena (double): ";
		std::cin >> elem->cena;
		append(head, elem);
	}
	/* Testy do wklejenia:
Pierwsz 11.11 Drugi 22.22 Trzeci 33.33 Czwarty 44.44 Piaty 55.55
Pierwsz -11.11 Drugi -22.22 Trzeci -11.11 Czwarty -44.44 Piaty -55.55
Pierwsz -11.11 Drugi 2.22 Trzeci 11.11 Czwarty 44.44 Piaty 5.55
	*/

	//2. Wydrukować utworzoną listę, korzystając z funkcji drukującej listę zaczynającą się pod jakimś
	//adresem.
	std::cout << std::endl << std::endl << "Zawartosc listy:" << std::endl;
	display(head);

	//3. Zamienić pierwszy element listy z elementem ostatnim.

	if (head != nullptr) //czy istnieje pierwszy element
	{
		if (head->next != nullptr) //czy sa przynajmniej 2 elementy
		{
			TTowar* secondlast = head;
			while (secondlast->next->next != nullptr) //szukamy przedostatniego elementu
				secondlast = secondlast->next;
			TTowar* last = secondlast->next;//to jest ostatni
			secondlast->next = head; //przedostatni wskazuje teraz na pierwszy jako na kolejny element
			last->next = head->next; //ostatni wskazuje na drugi jako na kolejny element
			head->next = nullptr; //pierwszy stal sie ostatni, za nim nic nie ma
			//pozostalo ustawic wskaznik na nowy poczatek i voila
			head = last;
		}
	}

	//4. Ponownie wydrukować listę.
	std::cout << std::endl << std::endl << "Zawartosc listy po zamianie pierwszego z ostatnim:" << std::endl;
	display(head);

	//5. Wydrukować nazwę produktu (lub kilku produktów) o najwyższej cenie.

	//mozna bylo zapamietac najwyzsza cene przy tworzeniu listy, ale mam wrazenie, ze chodzi
	//o nauke iterowania po listach
	if (head != nullptr) //czy istnieje pierwszy element
	{
		double top_price = head->cena;
		TTowar* tmp = head;
		while (tmp != nullptr)
		{
			if (tmp->cena > top_price)
				top_price = tmp->cena;
			tmp = tmp->next;
		}

		tmp = head; //wracamy na poczatek i drukujemy co trzeba
		std::cout << std::endl << std::endl << "Nazwy produktow o najwyzszej cenie:" << std::endl;
		while (tmp != nullptr)
		{
			if (tmp->cena == top_price)
				std::cout << tmp->nazwa << "\t" << tmp->cena << std::endl;
			tmp = tmp->next;
		}
	}

	//6. Skasować utworzoną listę korzystając z funkcji kasującej listę zaczynającą się pod jakimś adresem.
	deletelist(head);

	//7. Ponownie wydrukować listę.
	std::cout << std::endl << std::endl << "Lista po usunieciu elementow:" << std::endl;
	display(head);
}


/*
Algorytmy i Struktury Danych, lato 2020
Zadanie p1
1. Wczytać z klawiatury dane dotyczące pięciu produktów (nazwa, cena) i utworzyć z nich listę
jednokierunkową w kolejności zgodnej z wczytywaniem, wykorzystując funkcję, która dopisuje towar
o jakichś danych na końcu listy zaczynającej się pod jakimś adresem.
2. Wydrukować utworzoną listę, korzystając z funkcji drukującej listę zaczynającą się pod jakimś
adresem.
3. Zamienić pierwszy element listy z elementem ostatnim.
4. Ponownie wydrukować listę.
5. Wydrukować nazwę produktu (lub kilku produktów) o najwyższej cenie.
6. Skasować utworzoną listę korzystając z funkcji kasującej listę zaczynającą się pod jakimś adresem.
7. Ponownie wydrukować listę.

Uwaga 1: Słowo "jakiś" oznacza parametr funkcji.
Uwaga 2: Nie należy używać innych funkcji niż wyżej podane.
Uwaga 3: Wykonując różne działania na liście (pkt 2-7) należy założyć, że nie znamy ilości elementów
listy, więc trzeba uważać, aby nie odwoływać się do pola next elementu, który nie istnieje (czyli ma
adres NULL); w szczególności należy sprawdzać, czy lista nie jest pusta (adres głowy ==NULL) i czy ma
ona dosyć elementów (aby nie wykonywać operacji niemożliwych do wykonania).
*/