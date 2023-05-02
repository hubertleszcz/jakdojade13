#pragma once
#include<iostream>

struct RoadNode {
	int to;
	int length;
	RoadNode* next;
};

//po³¹czenia gwiazdek i hashtagow(kazda droga wynosi 1
class NeighbourhoodList {
private:
	int elements;
	RoadNode* start;
	RoadNode* end;

public:
	NeighbourhoodList() {
		elements = 0;
		start = nullptr;
		end = nullptr;
	}
	void AddNewNode(int to, int length) {
		RoadNode* newnode = new RoadNode;
		newnode->to = to;
		newnode->length = length;
		newnode->next = nullptr;

		if (start == nullptr) {
			start = newnode;
			end = newnode;
		}
		else {
			end->next = newnode;
			end = newnode;
		}

		elements++;
	}
	void PrintNodes(int a) const{
		RoadNode* currnode = start;
		while (currnode != nullptr) {
			std::cout << "From " << a << " to " << currnode->to << " length " << currnode->length << std::endl;
			currnode = currnode->next;
		}
	}

	RoadNode* GetNode(int i) const{
		RoadNode* currnode = start;
		for (int j = 0; j < i; j++) {
			currnode = currnode->next;
		}
		return currnode;
	}

	int GetSize() const{
		return elements;
	}

	void MemoryFree() {
		RoadNode* currnode = start;
		while (currnode != nullptr) {
			RoadNode* nextone = currnode->next;
			delete currnode;
			currnode = nextone;
		}
		elements = 0;
		start = nullptr;
		end = nullptr;
	}
	~NeighbourhoodList() {
	
	}
};


struct TownNode {
	int to;
	int length;
	TownNode* next;
	TownNode() {
		this->to = 0;
		this->length = 0;
		this->next = nullptr;
	}
	TownNode(int to, int length) {
		this->to = to;
		this->length = length;
		this->next = nullptr;
	}
};

class TownNeighbourhoodList {
private:
	int elements;
	TownNode* start;
	TownNode* end;

public:
	TownNeighbourhoodList() {
		elements = 0;
		start = nullptr;
		end = nullptr;
	}
	void AddNewNode(int to, int length) {
		TownNode* newnode = new TownNode;
		newnode->to = to;
		newnode->length = length;
		newnode->next = nullptr;

		if (start == nullptr) {
			start = newnode;
			end = newnode;
		}
		else {
			end->next = newnode;
			end = newnode;
		}

		elements++;
	}

	TownNode* GetNode(int i) const{
		TownNode* currnode = start;
		for (int j = 0; j < i; j++) {
			currnode = currnode->next;
		}
		return currnode;
	}

	int GetSize() const{
		return elements;
	}
	void MemoryFree() {
		TownNode* currnode = start;
		while (currnode != nullptr) {
			TownNode* nextnode = currnode->next;
			delete currnode;
			currnode = nextnode;
		}
		elements = 0;
		start = nullptr;
		end = nullptr;
	}
	~TownNeighbourhoodList() {
	
	}
};