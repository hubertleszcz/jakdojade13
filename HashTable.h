#pragma once
#include <string.h>
using namespace std;


struct Vortex {
	int id;
	int pos_x;
	int pos_y;
	char* name;
	TownNeighbourhoodList neighbours;
};

struct TableNode {
	int id;
	TableNode* next;
};
class HashTable {
private:
	int size;
	TableNode* Data;
public:
	HashTable() {

	}
	HashTable(int a) {
		this->size = a;
		Data = new TableNode[size];
		for (int i = 0; i < size; i++) {
			Data[i].id=-1;
		}
	}

	void AddNewElement(Vortex town) {
		int sum = 0;
		for (int i = 0; i < strlen(town.name); i++) {
			sum += (int)town.name[i];
		}
		int index = sum % size;

		TableNode* newNode = new TableNode;
		newNode->id = town.id;
		newNode->next = nullptr;

		if (Data[index].id == -1) {
			Data[index].id = newNode->id;
			Data[index].next = nullptr;
		}
		else {
			TableNode current = Data[index];
			while (current.next != nullptr) {
				current.id = current.next->id;
				current.next = current.next->next;
			}
			if (current.next != nullptr) {
				current.id = current.next->id;
				current.next = current.next->next;
			}
		}
	}

	int GetId(char* name, Vortex* towns) {
		int sum = 0;
		for (int i = 0; i < strlen(name); i++) {
			sum += (int)name[i];
		}
		int index = sum % size;

		TableNode current = Data[index];
		while (towns[current.id].name != name && current.next!=nullptr) {
			current.id = current.next->id;
			current.next = current.next->next;
		}
		return current.id;
	}

};
