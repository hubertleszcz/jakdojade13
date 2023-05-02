#pragma once
#include "NeighbourList.h"

class PriorityQueue {
private:
	int size;
	TownNode* data;
	int counter;
	int current;

	static void SwapNodes(TownNode* first, TownNode* second) {
		TownNode tmp = *first;
		*first = *second;
		*second = tmp;
	}
	
	void Heapify(int index) {
		if (index == 0) {
			return;
		}

		int parent = (index - 1) / 2;

		if (data[index].length < data[parent].length) {
			SwapNodes(&data[index], &data[parent]);
			Heapify(parent);
		}
		else {
			return;
		}
	}

	void ChildHeapify(int index) {
		int left = 2 * index + 1;
		int right = 2 * index + 2;
		int minimal = index;

		if (left < counter && data[left].length < data[minimal].length) {
			minimal = left;
		}

		if (right < counter && data[right].length < data[minimal].length) {
			minimal = right;
		}

		if (minimal != index) {
			SwapNodes(&data[index], &data[minimal]);
			ChildHeapify(minimal);
		}
	}
public:
	PriorityQueue(int size) {
		this->size = size;
		this->data = new TownNode[size];
		this->counter = 0;
		this->current = 0;
	}

	void AddNewElement(TownNode* newelement) {
		if (counter == size) {
			return;
		}

		data[counter] = *newelement;
		Heapify(counter);
		counter++;
	}


	TownNode GetShortest() {
		TownNode next_one = data[0];
		data[0] = data[counter - 1];
		counter--;

		ChildHeapify(0);
		return next_one;
	}
	bool IsEmpty() const{
		return counter == 0;
	}

	~PriorityQueue() {
		delete[] data;
	}
};