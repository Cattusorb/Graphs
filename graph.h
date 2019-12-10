#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

typedef struct Graph {
	int SIZE; // how many nodes there are in the graph
	int** distance; // 2D array of distances 0 or 1
	char** labels; // 1D array of char points, labels for vertexes
} Graph;

Graph* read_graph_file(const char*);
vector<int> get_neighbors(Graph*, int);
void print_graph(Graph*);

#endif
