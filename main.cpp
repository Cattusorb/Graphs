#include "graph.h"
#include <stack>
#include <queue>
#include <limits.h>

using namespace std;

const int INFINITY = INT_MAX;
const int NO_PREDECESSOR = -1;

/*
 * Function: print_path
 * ----------------------------
 *  Prints the path from a destination vertex to the source, using the
 *	predecessor array output from a search method
 *
 *   graph: graph that was searched, used for getting node labels
 *   prev: predecessor array fom a search method. prev[i] yields the index of
 *         vertex i's predecessor in a search begun at a source vertex.
 *		   prev[src] is defined to be the constant NO_PREDECESSOR (usually -1)
 *	 dst: index of destination vertex to trace back to source
 *
 */
 void print_path(Graph* graph, int* prev, int dst) {
	// Use a stack! Last-in-First-out
	stack<int> path;
	int current = dst;
	while (current != NO_PREDECESSOR)
    {
        path.push(current);
        current = prev[current];
    }

    while (!path.empty())
    {
        int v = path.top();
        path.pop();
        printf("%s ", graph->labels[v]);
    }
    printf("\n");
}

/*
 * Function: dfs
 * ----------------------------
 *  Searches a graph using a depth-first strategy
 *
 *	 graph: graph to search
 *	 src: index of source vertex to begin search from
 *
 *	returns: a predecessor array prev. prev[i] yields the index of
 *           vertex i's predecessor in a search begun at a source vertex.
 *		     prev[src] is defined to be the constant NO_PREDECESSOR (usually -1)
 *
 */
int* dfs(Graph* graph, int src) {
    bool discovered[graph->SIZE];
    int* prev = (int*)malloc(graph->SIZE * sizeof(int));
    for (int i = 0; i < graph->SIZE; i++)
    {
        prev[i] = NO_PREDECESSOR;
        discovered[i] = false;
    }

    stack<int> s;
    s.push(src);

    while(!s.empty())
    {
        int v = s.top();
        s.pop();

        if (!discovered[v])
        {
            discovered[v] = true;
            vector<int> neighbors = get_neighbors(graph, v);
            for (int n : neighbors)
            {
                s.push(n);

                if (!discovered[n])
                {
                    prev[n] = v;
                }
            }
        }
    }

    return prev;
}

/*
 * Function: bfs
 * ----------------------------
 *  Searches a graph using a breadth-first strategy
 *
 *	 graph: graph to search
 *	 src: index of source vertex to begin search from
 *
 *	returns: a predecessor array prev. prev[i] yields the index of
 *           vertex i's predecessor in a search begun at a source vertex.
 *		     prev[src] is defined to be the constant NO_PREDECESSOR (usually -1)
 *
 */
int* bfs(Graph* graph, int src) {
	bool discovered[graph->SIZE];
    int* prev = (int*)malloc(graph->SIZE * sizeof(int));
    for (int i = 0; i < graph->SIZE; i++)
    {
        prev[i] = NO_PREDECESSOR;
    }

    queue<int> q;
    q.push(src);
    discovered[src] = true;

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        vector<int> neighbors = get_neighbors(graph, v);
        for (int n : neighbors)
        {
            if (!discovered[n])
            {
                q.push(n);
                discovered[n] = true;
                prev[n] = v;
            }
        }
    }

    return prev;
}

int main() {
    Graph* graph = read_graph_file("graph.dat");
    print_graph(graph);

    int* predbfs = bfs(graph, 0);
    int* preddfs = dfs(graph, 0);

    print_path(graph, predbfs, 5);
    print_path(graph, preddfs, 5);
}
