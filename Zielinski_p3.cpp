//Zadanie p3
//Artur Zielinski 165095

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cassert>

//wezly drzewa
struct TNode {
	int val = 0;
	TNode* right = nullptr;
	TNode* left = nullptr;
};

//elementy listy
struct TElem {
	int val = 0;
	TElem* next = nullptr;
};

// DODAJ – dodaje jakas liczbe do drzewa znajdujacego sie pod jakims adresem i zwraca
//informacje logiczna, czy udalo sie wstawic te liczbe
bool DODAJ(TNode*& root, int value)
{
	if (root == nullptr) //tutaj trzeba dodac wezel
	{
		root = new TNode;
		root->val = value;
		root->left = nullptr;
		root->right = nullptr;
		return true;
	}
	else
	{
		if (value > root->val) //wieksze na prawo
			return DODAJ(root->right, value);
		else if (value < root->val) //mniejsze na lewo
			return DODAJ(root->left, value);
		else //rowne nie dodajemy - w BST nie powtarzaja sie wartosci wezlów
			return false;
	}
}

// WYSWIETL – wyswietla zawartosc drzewa znajdujacego sie pod jakims adresem na
// ekranie w porzadku inorder
void WYSWIETL(TNode* root)
{
	if (root != nullptr)
	{
		WYSWIETL(root->left); //najpierw lewe poddrzewo
		std::cout << root->val << " "; //potem wartosc wezla
		WYSWIETL(root->right);// na koncu prawe poddrzewo
	}
}

// ZNAJDZ – zwraca informacje logiczna, czy w drzewie znajdujacym sie pod jakims
//adresem wystepuje jakas liczba
bool ZNAJDZ(TNode* root, int value)
{
	if (root == nullptr) //w tym poddrzewie nie bylo szukanej wartosci
		return false;

	if (root->val == value) //znaleziona
		return true;
	else if (root->val > value) //mniejszych szukamy w lewym poddrzewie
		return ZNAJDZ(root->left, value);
	else
		return ZNAJDZ(root->right, value); //wiekszych w prawym
}

// WYSOKOSC – zwracaj wysokosc drzewa znajdujacego sie pod jakims adresem
int WYSOKOSC(TNode* root)
{
	if (root != nullptr)
	{
		int l = WYSOKOSC(root->left);//zliczamy wysokosc lewego poddrzewa
		int r = WYSOKOSC(root->right);//zliczamy wysokosc prawego poddrzewa
		return (l > r) ? ++l : ++r; //zwracamy wieksza wartosc z obu wysokosci +1 biezacy wezel
	}
	return 0;//brak wezla czyli nie zwiekszamy wysokosci
}

//? ROZMIAR – zwraca liczbe elementów w drzewie znajdujacym sie pod jakims adresem
int ROZMIAR(TNode* root)
{
	if (root != nullptr)
	{
		int cnt = ROZMIAR(root->left);//zliczamy rozmiar lewego poddrzewa
		cnt += ROZMIAR(root->right);//dodajemy rozmiar prawego poddrzewa
		cnt++;//dodajemy obecny wezel
		return cnt;
	}
	return 0;//brak wezla czyli nie zwiekszamy rozmiaru
}

//? MAKSIMUM – zwraca adres najwiekszej liczby w drzewie znajdujacym sie pod jakims
//adresem
//nie jestem pewny, czy chodzi o adres wezla czy adres wartosci w wezle?
//raczej chodzi o adres wartosci w wezle:
int* MAKSIMUM(TNode* root)
{
	if (root != nullptr)
	{
		while (root->right != nullptr) //szukamy po prostu prawego krancowego wezla
			root = root->right;
		return &(root->val);//zwracamy adres wartosci w wezle
	}
	return nullptr;//drzewi bylo puste
}
//alternatywnie adres samego wezla jesli o to chodzilo:
TNode* MAKSIMUM_2(TNode* root)
{
	if (root != nullptr)
		if (root->right != nullptr)
			return MAKSIMUM_2(root->right);
	return root;
}

//? USUN – usuwa cale drzewo znajdujace sie pod jakims adresem
void USUN(TNode*& root)
{
	if (root != nullptr)
	{
		USUN(root->left);//kasujemy lewe i prawe poddrzewo
		USUN(root->right);
		delete root;//kasujemy biezacy element
		root = nullptr;
	}
}

//? PRZEPISZ – przepisuje zawartosc drzewa znajdujacego sie pod jakims adresem w
//porzadku inorder do nowej listy jednokierunkowej i zwraca adres poczatku
//tej listy.
//uff.. to bylo dobre :)
TElem* PRZEPISZ(TNode* root)
{
	if (root == nullptr)
		return nullptr;

	TElem* head = PRZEPISZ(root->left);//tutaj przyjdzie poczatek listy z lewego poddrzewa
	TElem* e = new TElem; //tworzymy nowy element listy z biezaca wartoscia
	e->val = root->val;
	e->next = nullptr;

	if (head != nullptr) //jesli z lewego poddrzewa cos wrocilo
	{
		TElem* tmp = head;//musimy trzymac pierwszy element bo trzeba go zwrocic na koncu funkcji
		while (tmp->next != nullptr)//szukamy ostatniego elementu listy
			tmp = tmp->next;
		tmp->next = e;//i dopisujemy polaczenie do kolejnego elementu
	}
	else
		head = e;//lewe poddrzewo bylo puste wiec biezacy element bedzie pierwszym na liscie

	TElem* rhead = PRZEPISZ(root->right);//poczatek listy z prawego poddrzewa
	if (rhead != nullptr)
		e->next = rhead; //po prostu dopisujemy go na koncu listy
	return head;//zwracamy poczatek naszej calej listy
}

//? DODAJ2 – dodaje jakas liczbe calkowita na koncu listy zaczynajacej sie pod jakims
//adresem
void DODAJ2(TElem* &head, int val)
{
	TElem* e = new TElem;
	e->val = val;
	e->next = nullptr;
	if (head == nullptr)//lista jest pusta, dodajemy pierwszy element
		head = e;
	else
	{
		TElem* tmp = head;//nie mozemy ruszac head bo zmieni sie w main()
		while (tmp->next != nullptr)//iterujemy na koniec listy
			tmp = tmp->next;
		tmp->next = e;//i laczymy
	}
}

//? WYSWIETL2 – wyswietla liste zaczynajaca sie pod jakims adresem
void WYSWIETL2(TElem* head)
{
	if (head != nullptr)
	{
		std::cout << head->val << " ";
		WYSWIETL2(head->next);
	}
}

//? SORTUJ – sortuje liste zaczynajaca sie pod jakims adresem z zastosowaniem
//algorytmu MergeSort(dopisac funkcje pomocnicze w razie potrzeby)
TElem* SORTUJ(TElem* head)
{
	if (head == nullptr)//pusta lista
		return nullptr;
	if (head->next == nullptr)//jeden element, wiec posortowane
		return head;
	//od tego moment mamy co najmniej 2 elementy

	//musimy przerwac liste w polowie, najpierw trzeba zobaczyc, gdzie polowa jest
	int num = 0;
	for (TElem* t = head; t != nullptr; t = t->next)
		num++;
	num /= 2;//elementow jest min. 2, wiec nigdy nie wyjdzie 0

	TElem* left = head;//pierwsza czesc listy zaczyna sie na pierwszym elemencie
	TElem* right = nullptr;
	int i = 0;
	for (TElem* t = head; t != nullptr; t = t->next)
	{
		if (i++ == num - 1)//iterujemy do elementu poprzedzajacego polowe
		{
			right = t->next; //druga czesc zaczyna sie w polowie
			t->next = nullptr;//przerywamy polaczenie pomiedzy obiema listami
			break;
		}
	}

	//i dalej rekurencyjnie dzielimy listy na pól
	left = SORTUJ(left);
	right = SORTUJ(right);

	//teraz obie listy left, right beda posortowane - albo maja tylko 1 element,
	//albo zostana posortowane ponizej.
	//teraz trzeba polaczyc obie listy i utworzyc jedna posortowana liste
	//ktora zostanie polaczona w nastepnym zwrocie rekurencyjnym itd.
	TElem* sorted = nullptr, * stemp = nullptr;
	while (left != nullptr && right != nullptr)//wybieramy mniejeszy element z jednej lub drugiej listy
	{
		if (left->val <= right->val)
		{
			if (sorted == nullptr)
			{
				sorted = left; //lista wynikowa byla pusta, wiec to bedzie pierwszy element
				stemp = sorted;
				left = left->next;//bierzemy kolejny element z pierwszej listy
			}
			else
			{
				stemp->next = left; //podlaczamy kolejny element do listy wynikowej
				left = left->next;//bierzemy kolejny element z pierwszej listy
				stemp = stemp->next;//przestawiamy sie na koniec listy wynikowej
			}
		}
		else //analogicznie jak powyzej, ale dla drugiej listy
		{
			if (sorted == nullptr)
			{
				sorted = right;
				stemp = sorted;
				right = right->next;
			}
			else
			{
				stemp->next = right;
				right = right->next;
				stemp = stemp->next;
			}
		}
	}

	//teraz w pierwszej albo drugiej liscie mogly zostac jeszcze jakies elementy
	//trzeba je po prostu dolaczyc do listy wynikowej bo takze juz beda posortowane

	//aby tutaj dojsc lista musiala miec min. 2 elementy
	//wiec left i right zawsze beda mialy min. 1 element
	//zatem sorted i stmp bedzie juz utworzone w petli powyzej ^^^
	//wiec te asercje powinny byc spelnione
	assert(sorted != nullptr);
	assert(stemp != nullptr);

	while (left != nullptr)//dolaczamy wszystko z jednej i drugiej listy
	{
		stemp->next = left;
		left = left->next; 
		stemp = stemp->next;
	}
	while (right != nullptr)
	{
		stemp->next = right;
		right = right->next;
		stemp = stemp->next;
	}

	return sorted;
}

//USUN2 – usuwa liste zaczynajaca sie pod jakims adresem
void USUN2(TElem*& head)
{
	//najpierw sprawdzamy, czy jest co kasowac
	if (head == nullptr)
		return;

	//i kasujemy po kolei kazdy poprzedni element
	TElem* tmp = nullptr;
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
	//inicjalizujemy generator liczb losowych
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

//a) wypelnic drzewo kolejno liczbami : 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15 (bez interakcji z
//	uzytkownikiem)
	TNode* root = nullptr;
	DODAJ(root, 8);//w zasadzie w kazdym dodaj trzeba by sprawdzac czy sie udalo i cos napisac jesli nie
	DODAJ(root, 4);//ale z tego zestawu liczb wiemy, ze wszystko sie powiedzie
	DODAJ(root, 12);
	DODAJ(root, 2);
	DODAJ(root, 6);
	DODAJ(root, 10);
	DODAJ(root, 14);
	DODAJ(root, 1);
	DODAJ(root, 3);
	DODAJ(root, 5);
	DODAJ(root, 7);
	DODAJ(root, 9);
	DODAJ(root, 11);
	DODAJ(root, 13);
	DODAJ(root, 15);
//b) wypisac zawartosc drzewa na ekranie w porzadku inorder
	std::cout << "Zawartosc drzewa w porzadku inorder:" << std::endl;
	WYSWIETL(root);
//c) wyznaczyc wysokosc drzewa i wyswietlic ja na ekranie
	std::cout << std::endl << "Wysokosc drzewa: " << WYSOKOSC(root) << std::endl;
//d) dodac do drzewa 10 losowych liczb calkowitych z przedzialu <16,30>
	for (int i = 0; i < 10; i++)
	{
		int n = 16 + std::rand() % (30 - 16 + 1);
		if (!DODAJ(root, n))
			std::cout << "Nie udalo sie dodac do drzewa: " << n << std::endl;
	}
//e) ponownie wypisac zawartosc drzewa na ekranie w porzadku inorder
	std::cout << "Zawartosc drzewa w porzadku inorder:" << std::endl;
	WYSWIETL(root);
//f) wyswietlic informacje, jaka jest najwieksza liczba w drzewie
	int* a = MAKSIMUM(root);
	if (a != nullptr)
		std::cout << std::endl << "Najwieksza liczba w drzewie: " << *a << std::endl;
//g) wyswietlic informacje, ile liczb zawiera drzewo
	std::cout << "Drzewo zawiera " << ROZMIAR(root) << " liczb(y)." << std::endl;
//h) sprawdzic, czy w drzewie wystepuje liczba 22 i wyswietlic stosowny komunikat
	std::cout << "W drzewie " << (ZNAJDZ(root, 22) ? "" : "nie ") << "znajduje sie liczba 22." << std::endl;
//i) przepisac zawartosc drzewa w porzadku inorder do nowej listy jednokierunkowej
	TElem* head = nullptr;
	head = PRZEPISZ(root);
//j) usunac cale drzewo
	USUN(root);

	//Czesc z lista:

//a) wyswietlic zawartosc listy na ekranie
	std::cout << std::endl << "Zawartosc listy:" << std::endl;
	WYSWIETL2(head);
//b) dodac na koncu listy 10 losowych liczb calkowitych z przedzialu <31,50>
	for (int i = 0; i < 10; i++)
	{
		int n = 31 + std::rand() % (50 - 31 + 1);
		DODAJ2(head, n);
	}
//c) posortowac liste rosnaco z zastosowaniem algorytmu MergeSort
	head = SORTUJ(head);
//d) ponownie wyswietlic zawartosc listy na ekranie
	std::cout << std::endl << "Zawartosc listy:" << std::endl;
	WYSWIETL2(head);
//e) usunac liste
	USUN2(head);
}

/*
1. Napisac nastepujace funkcje umozliwiajace operacje na drzewie BST przechowujacym liczby
calkowite: (2pkt)
? DODAJ – dodaje jakas liczbe do drzewa znajdujacego sie pod jakims adresem i zwraca
informacje logiczna, czy udalo sie wstawic te liczbe
? WYSWIETL – wyswietla zawartosc drzewa znajdujacego sie pod jakims adresem na
ekranie w porzadku inorder
? ZNAJDZ – zwraca informacje logiczna, czy w drzewie znajdujacym sie pod jakims
adresem wystepuje jakas liczba
? WYSOKOSC – zwracaj wysokosc drzewa znajdujacego sie pod jakims adresem
? ROZMIAR – zwraca liczbe elementów w drzewie znajdujacym sie pod jakims adresem
? MAKSIMUM – zwraca adres najwiekszej liczby w drzewie znajdujacym sie pod jakims
adresem
? USUN – usuwa cale drzewo znajdujace sie pod jakims adresem
? PRZEPISZ – przepisuje zawartosc drzewa znajdujacego sie pod jakims adresem w
porzadku inorder do nowej listy jednokierunkowej i zwraca adres poczatku
tej listy.
Nastepnie korzystajac z napisanych funkcji:
a) wypelnic drzewo kolejno liczbami: 8,4,12,2,6,10,14,1,3,5,7,9,11,13,15 (bez interakcji z
uzytkownikiem)
b) wypisac zawartosc drzewa na ekranie w porzadku inorder
c) wyznaczyc wysokosc drzewa i wyswietlic ja na ekranie
d) dodac do drzewa 10 losowych liczb calkowitych z przedzialu <16,30>
e) ponownie wypisac zawartosc drzewa na ekranie w porzadku inorder
f) wyswietlic informacje, jaka jest najwieksza liczba w drzewie
g) wyswietlic informacje, ile liczb zawiera drzewo
h) sprawdzic, czy w drzewie wystepuje liczba 22 i wyswietlic stosowny komunikat
i) przepisac zawartosc drzewa w porzadku inorder do nowej listy jednokierunkowej
j) usunac cale drzewo
2. Nastepnie napisac nastepujace funkcje operujace na liscie jednokierunkowej: (2pkt)
? DODAJ2 – dodaje jakas liczbe calkowita na koncu listy zaczynajacej sie pod jakims
adresem
? WYSWIETL2 – wyswietla liste zaczynajaca sie pod jakims adresem
? SORTUJ – sortuje liste zaczynajaca sie pod jakims adresem z zastosowaniem
algorytmu MergeSort (dopisac funkcje pomocnicze w razie potrzeby)
? USUN2 – usuwa liste zaczynajaca sie pod jakims adresem
Nastepnie korzystajac z napisanych funkcji:
a) wyswietlic zawartosc listy na ekranie
b) dodac na koncu listy 10 losowych liczb calkowitych z przedzialu <31,50>
c) posortowac liste rosnaco z zastosowaniem algorytmu MergeSort
d) ponownie wyswietlic zawartosc listy na ekranie
e) usunac liste
Uwaga: slowo jakis oznacza parametr funkcji.
*/