#include "stdafx.h"
#include <iostream>

using namespace std;

struct Element {
	char module;
	Element* next;
	Element* prev;
};

class List {
private:
	Element* front;
	Element* back;
public:
	//konstruktor pustej listy
	List() {
		front = NULL;
		back = NULL;
	}
	//+element na początku listy 
	void add_front(Element *x) {
		x->prev = NULL;
		x->next = front;
		if (front!=NULL) front->prev = x;
		front = x;
		if (back==NULL) back = front;
	}
	//+element na końcu listy 
	void add_back(Element *x) {
		if (back!=NULL) back->next = x;
		x->next = NULL; 
		x->prev = back;
		back = x;
		if (front==NULL) front = back;
	}
	//usuwanie
	void RemoveFirst(){
		if (front == NULL) {
		}
		else {
			front = front->next;
			if (front == NULL) {
				back = NULL;
			}
			else {
				front->prev = NULL;
			}
		}
	}
	void RemoveLast() {
		if (back != NULL) {
			if (back == front) front = back = NULL;
			else {
				back = back->prev;
				back->next = NULL;
			}
		}
	}
	//funkcja wyświetlająca całą listę
	void PrintList() {
		Element *tmp;
		tmp = front;
		while (tmp != NULL) {
			cout << tmp->module;
			tmp = tmp->next;
		}
		cout << endl;
	}
	//destruktor
	~List() {
		Element *tmp;
		while (front!=NULL) {
			tmp = front->next;
			delete front;
			front = tmp;
		}
	}
};

int main()
{
	List caterpilar;
	
	char variable;
	//pobierane zmienne:
	int width, height, movements, x, y, lenght;
	cin >> width >> height >> movements >> y >> x >> lenght;
	for (int i = 0; i < lenght; i++) {
		cin >> variable;
		Element *k;
		k = new Element;
		k->module = variable;
		caterpilar.add_back(k);
	}
	//alokacja pamięci dla pola
	char **tab;
	tab = new char *[height];
	for (int j = 0; j < height; j++) {
		tab[j] = new char[width];
	}
	//cin pola
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			cin >> variable;
			tab[x][y] = variable;
		}
	}

	int direction = 5;//start w prawo
	x -= 1;
	y -= 1;
	//przemieszczanie się po polu gry
	for (int i = 0; i < movements; i++) {
		switch (tab[x][y])
		{
		case '1':
			direction = 1;
			break;
		case '2':
			direction = 2;
			break;
		case '3':
			direction = 3;
			break;
		case '4':
			direction = 4;
			break;
		case '#':
			tab[x][y] = '#';
			break;
		case '@':
			tab[x][y] = '@';
			break;
		case '.':
			caterpilar.RemoveFirst();
			lenght--;
			break;
		case '*':
			caterpilar.RemoveLast();
			lenght--;
			break;
		default:
			variable = tab[x][y];
			if (variable > 65 && variable < 91) {
				Element *k;
				k = new Element;
				k->module = variable+32;
				caterpilar.add_back(k);
				lenght++;
				tab[x][y] = --variable;
			}
			else if(variable >97 && variable <123){
				Element *k;
				k = new Element;
				k->module = variable;
				caterpilar.add_front(k);
				lenght++;
				tab[x][y] = --variable;
			}
			else if (variable == 97) {
				Element *k;
				k = new Element;
				k->module = variable;
				caterpilar.add_front(k);
				lenght++;
				tab[x][y] = '.';//a
			}
			else if (variable == 65) {
				Element *k;
				k = new Element;
				k->module = 'a';
				caterpilar.add_back(k);
				lenght++;
				tab[x][y] = '*';//A
			}		
			break;
		}
		//czy caterpilar nie zginął
		if (lenght < 1) {
			i = movements;
			cout << y + 1 << " " << x + 1 << " "; cout << '#' << endl;
		}
		//czy zostały wykonane wszystkie ruchy
		if (i == movements - 1) {
			cout << y + 1 << " " << x + 1 << " "; caterpilar.PrintList();
		}
		if (direction == 1) {//up
			x -= 1;
			if (x < 0) {
				x = height-1;
			}
		}
		else if (direction == 2) {//down
			x += 1;
			if (x > height-1) {
				x = 0;
			}
		}
		else if (direction == 3) {//left
			y -= 1;
			if (y < 0) {
				y = width-1;
			}
		}
		else if (direction == 4 || direction == 5) {//right
			y += 1;
			if (y > width-1) {
				y = 0;
			}
		}
		
	}
	//podmianka
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			if (tab[x][y] == '.' || tab[x][y]=='*') tab[x][y] = '@';
		}
	}
	//output
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			cout << tab[x][y];
		}
		cout << endl;
	}

	//zwolnienie pamięci

	delete[] * tab;
	system("pause");
    return 0;
}

