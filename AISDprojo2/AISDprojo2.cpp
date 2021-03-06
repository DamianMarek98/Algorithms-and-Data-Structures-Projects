#include "stdafx.h"
#include <iostream>
#include <limits.h>
using namespace std;

struct element {
	unsigned int value;
	int indexMax;
	int indexMin;
};
struct HeapElement {
	unsigned int value;
	int baseIndex;
};

void insertMax(HeapElement *Maxheap,element *base, unsigned int number,int size,int newSize,int toCheck) {
	while (newSize > 0 && Maxheap[toCheck].value < number)
	{
		int i = base[Maxheap[newSize].baseIndex].indexMax;
		base[Maxheap[toCheck].baseIndex].indexMax = i;
		base[Maxheap[newSize].baseIndex].indexMax = toCheck;
		swap(Maxheap[newSize], Maxheap[toCheck]);
		newSize = toCheck;
		toCheck = (newSize - 1) / 2;//New parent
	}
	Maxheap[newSize].value = number;

}
void insertMin(HeapElement *Minheap,element *base, unsigned int number, int size, int newSize, int toCheck) {
	while (newSize > 0 && Minheap[toCheck].value > number)
	{
		int i = base[Minheap[newSize].baseIndex].indexMin;
		base[Minheap[toCheck].baseIndex].indexMin = i;
		base[Minheap[newSize].baseIndex].indexMin = toCheck;
		swap(Minheap[newSize], Minheap[toCheck]);
		newSize = toCheck;
		toCheck = (newSize - 1) / 2;//New parent
	}
	Minheap[newSize].value = number;
}
void popMax(HeapElement *Maxheap,HeapElement *Minheap,element *base, int *size) {
	int Minposition = base[Maxheap[0].baseIndex].indexMin;
	int x = Minposition;
	*size = *size - 1;
	if (*size>0) {
		int last = Maxheap[*size].value;
		int a = base[Maxheap[0].baseIndex].indexMax;
		base[Maxheap[*size].baseIndex].indexMax = a;
		base[Maxheap[0].baseIndex].indexMax = *size;
		swap(Maxheap[0], Maxheap[*size]);
		int position = 0;
		int toCheck = 1;
		while (toCheck < *size) {
			if (toCheck + 1 <*size && Maxheap[toCheck + 1].value > Maxheap[toCheck].value) toCheck++;
			if (last >= Maxheap[toCheck].value) break;
			int a = base[Maxheap[toCheck].baseIndex].indexMax;
			base[Maxheap[position].baseIndex].indexMax = a;
			base[Maxheap[toCheck].baseIndex].indexMax = position;
			swap(Maxheap[position], Maxheap[toCheck]);
			position = toCheck;
			toCheck = (2 * toCheck) + 1;
		}
		Maxheap[position].value = last;
		//Delete form Minheap max element
		if (Minposition != *size) {
			last = Minheap[*size].value;
			a = base[Minheap[Minposition].baseIndex].indexMin;
			base[Minheap[*size].baseIndex].indexMin = a;
			base[Minheap[Minposition].baseIndex].indexMin = *size;
			swap(Minheap[Minposition], Minheap[*size]);
			//w górę
			if (Minheap[Minposition].value < Minheap[(Minposition - 1) / 2].value) {
				while (Minheap[Minposition].value < Minheap[(Minposition - 1) / 2].value) {
					a = base[Minheap[(Minposition - 1) / 2].baseIndex].indexMin;
					base[Minheap[Minposition].baseIndex].indexMin = a;
					base[Minheap[(Minposition - 1) / 2].baseIndex].indexMin = Minposition;
					swap(Minheap[(Minposition - 1) / 2], Minheap[Minposition]);
					Minposition = (Minposition - 1) / 2;
				}
			}// w dół
			else {
				position = Minposition;
				toCheck = (Minposition * 2) + 1;
				while (toCheck < *size) {
					if (toCheck + 1 < *size && Minheap[toCheck + 1].value < Minheap[toCheck].value) toCheck++;
					if (last <= Minheap[toCheck].value) break;
					int a = base[Minheap[toCheck].baseIndex].indexMin;
					base[Minheap[position].baseIndex].indexMin = a;
					base[Minheap[toCheck].baseIndex].indexMin = position;
					swap(Minheap[position], Minheap[toCheck]);
					position = toCheck;
					toCheck = (2 * toCheck) + 1;
				}
				Minheap[position].value = last;
			}
		}
	}
}
void popMin(HeapElement *Minheap,HeapElement *Maxheap, element *base, int *size) {
	int Maxposition = base[Minheap[0].baseIndex].indexMax;
	int x = Maxposition;
	*size = *size - 1;
	if (*size>0) {
		int last = Minheap[*size].value;
		int a = base[Minheap[0].baseIndex].indexMin;
		base[Minheap[*size].baseIndex].indexMin = a;
		base[Minheap[0].baseIndex].indexMin = *size;
		swap(Minheap[0], Minheap[*size]);
		int position = 0;
		int toCheck = 1;
		while (toCheck < *size) {
			if (toCheck + 1 <*size && Minheap[toCheck + 1].value < Minheap[toCheck].value) toCheck++;
			if (last <= Minheap[toCheck].value) break;
			int a = base[Minheap[toCheck].baseIndex].indexMin;
			base[Minheap[position].baseIndex].indexMin = a;
			base[Minheap[toCheck].baseIndex].indexMin= position;
			swap(Minheap[position], Minheap[toCheck]);
			position = toCheck;
			toCheck = (2 * toCheck) + 1;
		}
		Minheap[position].value = last;
		//Delete form Maxheap min 
		if (Maxposition != *size) {
			last = Maxheap[*size].value;
			a = base[Maxheap[Maxposition].baseIndex].indexMax;
			base[Maxheap[*size].baseIndex].indexMax = a;
			base[Maxheap[Maxposition].baseIndex].indexMax = *size;
			swap(Maxheap[Maxposition], Maxheap[*size]);
			//w górę
			if (Maxheap[Maxposition].value > Maxheap[(Maxposition - 1) / 2].value) {
				while (Maxheap[Maxposition].value > Maxheap[(Maxposition - 1) / 2].value) {
					a = base[Maxheap[(Maxposition - 1) / 2].baseIndex].indexMax;
					base[Maxheap[Maxposition].baseIndex].indexMax = a;
					base[Maxheap[(Maxposition - 1) / 2].baseIndex].indexMax = Maxposition;
					swap(Maxheap[(Maxposition - 1) / 2], Maxheap[Maxposition]);
					Maxposition = (Maxposition - 1) / 2;
				}
			}


			position = Maxposition;
			toCheck = (Maxposition - 1) / 2;
			while (position > 0 && Maxheap[toCheck].value < last)
			{
				int i = base[Maxheap[position].baseIndex].indexMax;
				base[Maxheap[position].baseIndex].indexMax = i;
				base[Maxheap[position].baseIndex].indexMax = toCheck;
				swap(Maxheap[position], Maxheap[toCheck]);
				position = toCheck;
				toCheck = (position - 1) / 2;//New parent
			}
			Maxheap[position].value = last;
		}
	}
}
int main()
{
	int n,size=0;
	cin >> n;
	//Tworzenie kopca
	HeapElement * Maxheap= new HeapElement[n];
	HeapElement * Minheap = new HeapElement[n];
	element * base = new element[n];
	long long int number;
	for (int k = 0; k < n; k++) {
		Maxheap[k].baseIndex=k;
		Minheap[k].baseIndex=k;
		base[k].indexMax = k;
		base[k].indexMin = k;
		cin >> number;
		if (number > UINT_MAX) {
			number = 0;
		}
		int newSize = size++;
		int toCheck = (newSize - 1) / 2;//parent
		if (number != 0 || number != 1) {
			insertMax(Maxheap, base, number, size, newSize, toCheck);
			insertMin(Minheap, base, number, size, newSize, toCheck);
		}
		base[k].value = number;
	}


	int q;
	cin >> q;
	int k;
	char c;
	for (int j = 0; j < q; j++) {
		cin >> k >> c;
		for (int i = 0; i < k; i++) {
			if (size > 0) {
				switch (c) {
				case 'l'://largest
					if (Maxheap[0].value % 2 == 0) {
						unsigned int l = Maxheap[0].value / 2;
						int index = Maxheap[0].baseIndex;
						popMax(Maxheap, Minheap, base, &size);
						int newSize = size++;
						int toCheck = (newSize - 1) / 2;//parent
						insertMax(Maxheap, base, l, size, newSize, toCheck);
						insertMin(Minheap, base, l, size, newSize, toCheck);
						base[index].value = l;
					}
					else {
						long long int uint = Maxheap[0].value;
						long long int check = (3 * uint) + 1;
						if (check > UINT_MAX) {
							base[Maxheap[0].baseIndex].value = 0;
							popMax(Maxheap, Minheap, base, &size);
						}
						else {
							unsigned int l = (3 * Maxheap[0].value) + 1;
							int index = Maxheap[0].baseIndex;
							popMax(Maxheap, Minheap, base, &size);
							int newSize = size++;
							int toCheck = (newSize - 1) / 2;//parent
							insertMax(Maxheap, base, l, size, newSize, toCheck);
							insertMin(Minheap, base, l, size, newSize, toCheck);
							base[index].value = l;
						
						}
					}
					break;
				case 's'://smallest
					while (Minheap[0].value == 1) {
						popMin(Minheap, Maxheap, base, &size);
					}
					if (Minheap[0].value % 2 == 0) {
						unsigned int l = Minheap[0].value / 2;
						//indexy?!?
						int index = Minheap[0].baseIndex;
						popMin(Minheap, Maxheap, base, &size);
						int newSize = size++;
						int toCheck = (newSize - 1) / 2;//parent
						insertMax(Maxheap, base, l, size, newSize, toCheck);
						insertMin(Minheap, base, l, size, newSize, toCheck);
						base[index].value = l;
					
					}
					else {
						long long int check = (3 * Minheap[0].value) + 1;
						if (check < UINT_MAX) {
							unsigned int l = (3 * Minheap[0].value) + 1;
							//indexy?!?
							int index = Minheap[0].baseIndex;
							popMin(Minheap, Maxheap, base, &size);
							int newSize = size++;
							int toCheck = (newSize - 1) / 2;//parent
							insertMax(Maxheap, base, l, size, newSize, toCheck);
							insertMin(Minheap, base, l, size, newSize, toCheck);
							base[index].value = l;
						
						}
						else {
							base[Minheap[0].baseIndex].value = 0;
							popMin(Minheap, Maxheap, base, &size);
						}
					}
				}
			}

			if (Maxheap[0].value == 0 || Maxheap[0].value == 1) {
				popMax(Maxheap, Minheap, base, &size);
			}
			if (Minheap[0].value == 0 || Maxheap[0].value == 1) {
				popMin(Minheap, Maxheap, base, &size);
			}

		}
	}
	

	for (int i = 0; i < n; i++) {
		if (base[i].value == 0) {
			cout << "m ";
		}
		else
		{
			cout << base[i].value << " ";
		}
	}
    return 0;
}

