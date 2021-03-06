#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class MaxHeap {
public:
	int MaxSize;
	int size;
	int *heap;

	MaxHeap(int Max) {
		MaxSize = Max;
		size = 0;
		heap = (int*)malloc(MaxSize * sizeof(int));
	}

	void MaxHeap::insertMax(int number) {
		int newSize = size++;
		if (newSize > MaxSize-1) {
			heap = (int*)realloc(heap, (MaxSize*2) * sizeof(int));
			MaxSize = MaxSize * 2;
		}
		int toCheck = (newSize - 1) / 2;//parent
		while (newSize > 0 && heap[toCheck]< number)
		{
			swap(heap[newSize], heap[toCheck]);
			newSize = toCheck;
			toCheck = (newSize - 1) / 2;//New parent
		}
		heap[newSize] = number;
	}

	void MaxHeap::popMax() {
		int s = size;
		size -= 1;
		if (s > 0) {
			int last = heap[s];
			swap(heap[0], heap[size+1]);
			int position = 0;
			int toCheck = 1;
			while (toCheck < s) {
				if (toCheck + 1 < s && heap[toCheck + 1] > heap[toCheck]) toCheck++;
				if (last >= heap[toCheck]) break;
				swap(heap[position], heap[toCheck]);
				position = toCheck;
				toCheck = (2 * toCheck) + 1;
			}
			heap[position] = last;
		}
	}

	void MaxHeap::increase(int oldValue, int newValue) {
		int Maxposition;
		int counter = 0;
		for (int i = 0; i < size; i++) {
			if (heap[i] == oldValue && counter == 0) {
				Maxposition = i;
				i = size;
				counter++;
			}
		}
		if(counter == 1){
			if (Maxposition != size && counter == 1) {
				//w górę
				if (newValue > heap[(Maxposition - 1) / 2]) {
					while (newValue > heap[(Maxposition - 1) / 2] && Maxposition != 0) {
						swap(heap[(Maxposition - 1) / 2], heap[Maxposition]);
						Maxposition = (Maxposition - 1) / 2;
					}
				}
				int position = Maxposition;
				int toCheck = (Maxposition - 1) / 2;
				while (position > 0 && heap[toCheck] < newValue)
				{
					swap(heap[position], heap[toCheck]);
					position = toCheck;
					toCheck = (position - 1) / 2;//New parent
				}
				heap[position] = newValue;
			}
		}
		else  printf("na\n");
	}

	void MaxHeap::print() {
		int * Tab = new int[size];
		int a = size;
		for(int i=0;i<size;i++){
			Tab[i] = heap[0];
			popMax();
		}
		for (int j=0; j < a; j++) {
			insertMax(Tab[j]);
			printf("%d\n", Tab[j]);
		}
		delete[] Tab;
	}
};

void merge(MaxHeap *to, MaxHeap *from) {
	while (from->size> 0) {
		int nValue = from->heap[0];
		to->insertMax(nValue);
		from->popMax();
	}
}

int main()
{

	MaxHeap *base[1000];
	for (int i = 0; i < 1000; i++) base[i] = new MaxHeap(100);
	

	int n, group, newValue, oldValue, group2;
	char command;
	int counter = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> command;
		switch (command)
		{
		case 'a':
			scanf("%d", &group);
			scanf("%d", &newValue);
			base[group]->insertMax(newValue);
			break;
		case 'e':
			scanf("%d", &group);
			if (base[group]->size-1< 0) {
				printf("na\n");
			}
			else {
				printf("%d\n", base[group]->heap[0]);
				base[group]->popMax();
			}
			break;
		case 'p':
			scanf("%d", &group);
			if(base[group]->size>0) base[group]->print();
			break;
		case 'm':
			scanf("%d", &group);
			scanf("%d", &group2);
			merge(base[group], base[group2]);
			break;
		case 'i':
			scanf("%d", &group);
			scanf("%d", &oldValue);
			scanf("%d", &newValue);
			if (base[group]->size == 0) {
				printf("na\n");
			}
			else {
				base[group]->increase(oldValue, newValue);
			}
			break;
		default: break;
		}
	}

    return 0;
}

