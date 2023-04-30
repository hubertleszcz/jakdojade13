#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "NeighbourList.h"
#include "HashTable.h"
#include "PriorityQueue.h"
#include "FIFOQueue.h"
using namespace std;

#define BASIC_DISTANCE 1
#define INF basics.width*basics.height


struct Basics {
    int width;
    int height;
    int town_counter;
    int road_cells;
};





void CreateMap(char** Map, Basics& basics, RoadVortex* roads, int** Ids) {
    int current = 0;
    for(int i = 0; i < basics.height * basics.width; i++) {
        char c = getchar();
        if (c == '\n') {
            i--;
            continue;
        }
        else {
            Map[i / basics.width][i % basics.width] = c;

            if (Map[i / basics.width][i % basics.width] == '#' || Map[i / basics.width][i % basics.width] == '*') {
                Ids[i / basics.width][i % basics.width] = current;
                if (Map[i / basics.width][i % basics.width]=='*') {
                    basics.town_counter++;
                    basics.road_cells++;
                    roads[current].is_a_town = true;
                }
                else {
                    roads[current].is_a_town = false;
                    basics.road_cells++;

                }
                roads[current].id = current;
                roads[current].x = i % basics.width;
                roads[current].y = i / basics.width;
                current++;
            }
        }
    }
}

void MemoryFree(char** Map, int height, Vortex* towns, int townscounter) {
    for (int i = 0; i < height; i++) {
        delete[] Map[i];
    }
    delete[] Map;
    for (int i = 0; i < townscounter; i++) {
        delete[] towns[i].name;
    }
}

bool IsValid(char x) {
    if (x != '.' && x != '#' && x != '*') return true;
    return false;
}

void reverse(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

char* FindInAdjacentRow(char* row, int i, int j, Basics basics) {
    int right = j + 1;
    int left = j - 1;
    int index = 0;
    char* name = new char[basics.width+1];

    if (j == basics.width - 1 && IsValid(row[left]) && !IsValid(row[j])) {
        while (left >= 0 && IsValid(row[left])) {
            name[index++] = row[left--];
        }
        if (index > 0) {
            name[index] = '\0';
            reverse(name);
            return name;
        }
    }

    if (IsValid(row[right]) && !IsValid(row[j])) {
        while (right < basics.width && IsValid(row[right])) {
            name[index++] = row[right++];
        }
    }
    else if (IsValid(row[right]) && !IsValid(row[right + 1])) {
        while (right >= 0 && IsValid(row[right])) name[index++] = row[right--];
        if (index > 0) {
            name[index] = '\0';
            reverse(name);
            return name;
        }
    }
    else if(IsValid(row[j]) && j==0 && basics.width == 1) name[index++] = row[j];
    
    else if (IsValid(row[j]) && !IsValid(row[left])) {
        name[index++] = row[j];
        while (right < basics.width && IsValid(row[right])) {
            name[index++] = row[right++];
        }
    }
    else if (IsValid(row[j]) && !IsValid(row[right])) {
        while (j >= 0 && IsValid(row[j])) {
            name[index++] = row[j--];
        }
        if (index > 0) {
            name[index] = '\0';
            reverse(name);
            return name;
        }
    }
    else if (IsValid(row[left]) && !IsValid(row[left-1])) {
        while (left < basics.width && IsValid(row[left])) {
            name[index++] = row[left++];
        }
    }
    else {
        while (left >= 0 && IsValid(row[left])) {
            name[index++] = row[left--];
        }
        if (index > 0) {
            name[index] = '\0';
            reverse(name);
            return name;
        }
    }
    name[index] = '\0';
    return name;
}






void FindTown(char** Map, int i, int j, Basics basics, char*& name) {
    int right = j + 1;
    int left = j - 1;
    int up = i - 1;
    int down = i + 1;
    int index = 0;
    if (left >= 0 && IsValid(Map[i][left])) {
        while (left > 0 && IsValid(Map[i][--left]));
        while (Map[i][left] != '*') {
            if (IsValid(Map[i][left])) {
                name[index++] = Map[i][left];
            }
            left++;

        }
        name[index] = '\0';

    }
    else if (right < basics.width && IsValid(Map[i][right])) {
        while (right < basics.width && IsValid(Map[i][right])) {
            name[index++] = Map[i][right++];
        }
        name[index] = '\0';
    }
    else {
        if (up >= 0 && (IsValid(Map[up][j]) ||
           (left >= 0 && IsValid(Map[up][left])) ||
           (right < basics.width && IsValid(Map[up][right])))) {
                strcpy(name,FindInAdjacentRow(Map[up], i, j, basics));
        }
        else if (down < basics.height && (IsValid(Map[down][j]) ||
            (left >= 0 && IsValid(Map[down][left])) || 
            (right < basics.width && IsValid(Map[down][right])))) {
                strcpy(name, FindInAdjacentRow(Map[down], i, j, basics));
        }
    }
}
void TownFinder(char** Map, Vortex* towns, Basics basics, HashTable hash) {
    int visited_towns = 0;
    for (int i = 0; i <basics.height; i++) {
        for (int j = 0; j < basics.width; j++) {
            if (Map[i][j] == '*'){
                towns[visited_towns].name = new char[basics.width];
                towns[visited_towns].id = visited_towns;
                towns[visited_towns].pos_x = j;
                towns[visited_towns].pos_y = i;
                FindTown(Map, i, j, basics, towns[visited_towns].name);
               // hash.AddNewElement(towns[visited_towns]);
                visited_towns++;
            }
        }
        if (visited_towns == basics.town_counter) {
            break;
        }
    }
}


int BFS(Vortex* towns, RoadVortex* roads, Basics basics, int start, int to) {
    for (int i = 0; i < basics.road_cells; i++) {
        roads[i].visited = false;
        roads[i].dist = INF;
    }

    FIFOQueue queue(basics.road_cells);
    roads[start].dist = 0;
    queue.AddNewElement(roads[start]);

    while (!queue.IsAtTheEnd()) {
        RoadVortex current_vortex = queue.ReturnFirst();

        for (int i = 0; i < current_vortex.roadneighbours.GetSize(); i++) {
            int neighbour_id = current_vortex.roadneighbours.GetNode(i)->to;
            RoadVortex& neighbour = roads[neighbour_id];

            if (!neighbour.visited) {
                neighbour.visited = true;
                neighbour.dist = current_vortex.dist + 1;
                if (neighbour.is_a_town && neighbour.id != start && neighbour.id != to) {
                    neighbour.dist++;
                }
                if (neighbour.id == to) {
                    return neighbour.dist;
                }

                queue.AddNewElement(neighbour);
            }
        }
    }
    return INF;
}






void RoadFinder(char** Map, Vortex* towns, Basics basics, RoadVortex* roads, int** Ids) {
    int* tmp_town_indexes = new int[basics.town_counter];
    int current = 0;
   
    int visited_roads = 0;
    int visited_towns = 0;
    for (int i = 0; i < basics.height; i++) {
        for (int j = 0; j < basics.width; j++) {
            if (Map[i][j] == '#' || Map[i][j]=='*') {
                if (i > 0 && (Map[i - 1][j] == '*' || Map[i - 1][j] == '#')) {
                    roads[visited_roads].roadneighbours.AddNewNode(Ids[i-1][j], BASIC_DISTANCE);
                }
                if (j > 0 && (Map[i][j - 1] == '*' || Map[i][j - 1] == '#')) {
                    roads[visited_roads].roadneighbours.AddNewNode(Ids[i][j-1], BASIC_DISTANCE);

                }
                if (i < basics.height - 1 && (Map[i + 1][j] == '*' || Map[i + 1][j] == '#')) {
                    roads[visited_roads].roadneighbours.AddNewNode(Ids[i+1][j], BASIC_DISTANCE);
                }
                if (j < basics.width - 1 && (Map[i][j + 1] == '*' || Map[i][j + 1] == '#')) {
                    roads[visited_roads].roadneighbours.AddNewNode(Ids[i][j+1], BASIC_DISTANCE);
                }

                if (Map[i][j] == '*') {
                    tmp_town_indexes[visited_towns++] = visited_roads;
                }

                visited_roads++;
            }

        }
        if (visited_roads == basics.road_cells) break;
    }
    for (int i = 0; i < basics.town_counter; i++) {
        if (roads[tmp_town_indexes[i]].roadneighbours.GetSize() > 0) {
            for (int j = i + 1; j < basics.town_counter; j++) {
                int distance = BFS(towns, roads, basics, tmp_town_indexes[i], tmp_town_indexes[j]);
                towns[i].neighbours.AddNewNode(j, distance);
                towns[j].neighbours.AddNewNode(i, distance);
            }
        }
        towns[i].neighbours.AddNewNode(i, 0);
    }
    delete[] tmp_town_indexes;
}

void CreateName(char* name) {
    int index = 0;
    char c = getchar();
    while (c != ' '){ 
        if (c != '\n') {
            name[index++] = c;
        }
        c = getchar();
    }
    name[index] = '\0';
}

int FindIndex(char* name, Vortex* towns, Basics basics) {
    for (int i = 0; i < basics.town_counter; i++) {
        if (!strcmp(name, towns[i].name)) {
            return i;
        }
    }
    return basics.town_counter;
}
void FlightsHandler(Vortex* towns, Basics basics, HashTable hash) {
    char* from = new char[basics.width];
    char* to = new char[basics.width];
    int length, index_from, index_to;
    CreateName(from);
    CreateName(to);

    cin >> length;
    
    index_from = FindIndex(from, towns, basics);
    index_to = FindIndex(to, towns, basics);
   /* index_from = hash.GetId(from, towns);
    index_to = hash.GetId(to, towns);*/


    towns[index_from].neighbours.AddNewNode(index_to, length);

    delete[] from;
    delete[] to;
}


void OutputGenerator(int from, int to, int mode, Vortex* towns, Basics basics) {
    int shortest_path = 0;
    int* distances = new int[basics.town_counter];
    int* previous_towns = new int[basics.town_counter];
    bool* visited = new bool[basics.town_counter];
    for (int j = 0; j < basics.town_counter; j++) {
        if (from == j) {
            distances[j] = 0;
        }
        else {
            distances[j] = INF;
        }
        visited[j] = false;
    }

    PriorityQueue p_queue = PriorityQueue(basics.town_counter);
    p_queue.AddNewElement(new TownNode(from, 0));

    while (visited[to] == false && !p_queue.IsEmpty()) {
        TownNode current_node = p_queue.GetShortest();

        int current_vort = current_node.to;

        if (visited[current_vort]) {
            continue;
        }

        visited[current_vort] = true;

        for (int i = 0; i < towns[current_vort].neighbours.GetSize(); i++) {
            int new_id = towns[current_vort].neighbours.GetNode(i)->to;
            int new_dist = towns[current_vort].neighbours.GetNode(i)->length;
            int distance = distances[current_vort] + new_dist;

            if (distance < distances[new_id]) {
                distances[new_id] = distance;
                previous_towns[new_id] = current_vort;
            }
        }

        int next_vort = -1;
        int next_dist = INF;
        for (int i = 0; i < basics.town_counter; i++) {
            if (visited[i]) {
                continue;
            }
            if (distances[i] < next_dist) {
                next_vort = i;
                next_dist = distances[i];
            }
        }

        if (next_vort != -1) {
            p_queue.AddNewElement(new TownNode(next_vort, next_dist));
        }
    }

    if (distances[to] == INF) {
        shortest_path = INF;
    }
    else {
        shortest_path = distances[to];
    }
    printf("%d ", shortest_path);
    if (mode) {
        int current_town = to;
        int* path = new int[basics.town_counter];
        int path_length = 0;

        while (current_town != from) {
            path[path_length++] = current_town;
            current_town = previous_towns[current_town];
        }

        for (int i = path_length - 1; i > 0; i--) {
            cout << towns[path[i]].name << " ";
        }
    }

    cout << "\n";
    delete[] previous_towns;
    delete[] distances;
    delete[] visited;
}


void CommandsHandler(Vortex* towns, Basics basics) {
    char* from = new char[basics.width];
    char* to = new char[basics.width];
    int mode, index_from, index_to;
    CreateName(from);
    CreateName(to);

    cin >> mode;

    index_from = FindIndex(from, towns, basics);
    index_to = FindIndex(to, towns, basics);

    OutputGenerator(index_from, index_to, mode, towns, basics);

    delete[] from;
    delete[] to;
}

int main() {
    char** Map;
    int** Ids;
    int flights, commands;
    Basics basics;
    basics.town_counter = 0, basics.road_cells = 0;
    cin >> basics.width >> basics.height;
    Map = new char* [basics.height];
    Ids = new int* [basics.height];
    for (int i = 0; i < basics.height; i++) {
        Map[i] = new char[basics.width];
        Ids[i] = new int[basics.width];
    }
    RoadVortex* roads = new RoadVortex[basics.width*basics.height];

    CreateMap(Map, basics, roads,Ids);
    HashTable hash(2 * basics.town_counter);
    Vortex* towns = new Vortex[basics.town_counter];
    TownFinder(Map, towns, basics, hash);
    RoadFinder(Map, towns, basics, roads, Ids);
    
    
    cin >> flights;
    for (int i = 0; i < flights; i++) {
        FlightsHandler(towns, basics,hash);
    }
    cin >> commands;
    for (int i = 0; i < commands; i++) {
        CommandsHandler(towns, basics);
    }

    MemoryFree(Map, basics.height, towns,basics.town_counter);

    delete[] towns;
    delete[] roads;
    return 0;
}