#include "graph.h"

// Maximum number of characters in a vertex label
const int LABEL_LENGTH = 128;

// Maximum number of characters for a graph's string representation
const int STRING_LENGTH = 2048;

/*
 * Function: read_graph_file
 * ----------------------------
 *	Reads a data file and returns a pointer to the corresponding graph object
 *
 */
Graph* read_graph_file(const char* filename) {
	FILE* fp = fopen(filename, "r");

	// Get graph size
	int n;
	fscanf(fp, "%d\n", &n);
	Graph* graph = (Graph*) malloc(sizeof(Graph));
	graph->SIZE = n;

	// Set up vertex labels
	graph->labels = (char**) malloc(n * sizeof(char*));
	for (int i = 0; i < n; i++) {
		// Read line
		char line[LABEL_LENGTH];
		fgets(line, LABEL_LENGTH, fp);

		// Trim the newline character
		size_t len = strlen(line);
		if (line[len - 1] == '\n') {
			line[len - 1] = '\0';
		}

		// Allocate memory for this label and copy
		graph->labels[i] = (char*) malloc(LABEL_LENGTH * sizeof(char));
		strcpy(graph->labels[i], line);
	}

	// Set up adjacency matrix
	// First allocate memory for it and initialiize all elements to 0
	graph->distance = (int**) malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		graph->distance[i] = (int*) malloc(n * sizeof(int));
		for (int j = 0; j < n; j++) {
			graph->distance[i][j] = 0;
		}
	}

	// Now read the rest of the file which contains the edge pairs and costs.
	// The pattern is i j c, meaning traversing from vertex i to vertex j
 	// has cost c
	int i;
	int j;
	int cost;
	while (fscanf(fp, "%d %d %d", &i, &j, &cost) != EOF) {
		graph->distance[i][j] = cost;
	}

	fclose(fp);
	return graph;
}


/*
 * Function: get_neighbors
 * ----------------------------
 *  Returns a vector of the indices of the neighbors of vertex i in a graph
 *
 */
vector<int> get_neighbors(Graph* graph, int i) {
	vector<int> neighbors;

	for (int j = 0; j < graph->SIZE; j++) {
        if (graph->distance[i][j] != 0) {
            neighbors.push_back(j);
        }
	}

	return neighbors;
}

/*
 * Function: graph_as_string
 * ----------------------------
 * returns a string representation of a graph
 *
 */
void print_graph(Graph* graph) {
    printf("Graph:");
	for (int i = 0; i < graph->SIZE; i++) {
        for (int j = 0; j < graph->SIZE; j++) {
            if (graph->distance[i][j] != 0) {
                // Add a line of the form labels[i]->labels[j]: cost
                printf("\n%s -> %s: %d",
                        graph->labels[i],
                        graph->labels[j],
                        graph->distance[i][j]);
            }
        }
	}
    printf("\n");
}

