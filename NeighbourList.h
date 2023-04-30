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
	void PrintNodes(int a) {
		RoadNode* currnode = start;
		while (currnode != nullptr) {
			std::cout << "From " << a << " to " << currnode->to << " length " << currnode->length << std::endl;
			currnode = currnode->next;
		}
	}

	RoadNode* GetNode(int i) {
		RoadNode* currnode = start;
		for (int j = 0; j < i; j++) {
			currnode = currnode->next;
		}
		return currnode;
	}

	int GetSize() {
		return elements;
	}
};


struct TownNode {
	int to;
	int length;
	TownNode* next;
	TownNode() {

	}
	TownNode(int to, int lenght) {
		this->to = to;
		this->length = length;
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

	TownNode* GetNode(int i) {
		TownNode* currnode = start;
		for (int j = 0; j < i; j++) {
			currnode = currnode->next;
		}
		return currnode;
	}

	int GetSize() {
		return elements;
	}
};