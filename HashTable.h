#pragma once
#include <string.h>
using namespace std;

#define HASHPRIME 31
#define HASH 5381
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

class HashList {
private:
	TableNode* start;
	TableNode* end;
	int elements;
public:
	HashList() {
		start = nullptr;
		end = nullptr;
		elements = 0;
	}

	void AddNewNode(int id) {
		TableNode* newNode = new TableNode;
		newNode->next = nullptr;
		newNode->id = id;
		if (start == nullptr) {
			start = newNode;
			end = newNode;
		}
		else {
			end->next = newNode;
			end = newNode;
		}

		elements++;
	}
	int GetSize() const{
		return elements;
	}
	TableNode* GetStart() const{
		return start;
	}

	void MemoryFree() {
		TableNode* current = start;
		while (current != nullptr) {
		TableNode* tmp = current->next;
		delete current;
		current = tmp;
	 }
	}
	~HashList() {
		
    }
};
class HashTable {
private:
	int size;
	HashList* Data;
public:
	HashTable() {
		size = 0;
		Data = nullptr;
	}
	explicit HashTable(int a) {
		this->size = a;
		Data = new HashList[a];
	}

	static unsigned int FNVHash(const char* str){
		unsigned int hash = HASH;
		for (unsigned int i = 0; i < strlen(str); i++) {
			hash ^= unsigned int(str[i]);
			hash *= HASHPRIME;
		}
		return hash;
	}
	void AddNewElement(const char* name, int id) {
		const unsigned int hash = FNVHash(name) % size;
		Data[hash].AddNewNode(id);
	}
	int GetID(const char* name, Vortex* towns) const {
		const unsigned int hash = FNVHash(name) % size;
		TableNode* current = Data[hash].GetStart();
		while (current != nullptr) {
			if (!strcmp(name, towns[current->id].name)) {
				return current->id;
			}
			current = current->next;
		}
		return 0;
	}
	void Free() {
		for (int i = 0; i < size; i++) {
			Data[i].MemoryFree();
		}
		delete[] Data;
	}
	~HashTable(){
	}
};
