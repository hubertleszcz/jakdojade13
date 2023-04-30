#pragma once
#include "NeighbourList.h"

struct RoadVortex {
    bool visited;
    bool is_a_town;
    int id;
    int x;
    int y;
    int dist;
    NeighbourhoodList roadneighbours;
};

class FIFOQueue {
private:
    int size;
    RoadVortex* data;
    int current;
    int counter;
public:
    FIFOQueue(int size) {
        this->size = size;
        data = new RoadVortex[size];
        current = 0;
        counter = 0;
    }
    void AddNewElement(RoadVortex newelement) {
        data[counter] = newelement;
        counter++;
    }
    RoadVortex ReturnFirst() {
        RoadVortex next_one = data[current];
        current++;
        return next_one;
    }

    bool IsAtTheEnd() {
        if (counter == current) {
            return true;
        }
        return false;
    }

    int GetSize() {
        return counter;
    }
    ~FIFOQueue() {
        delete[] data;
    }
};