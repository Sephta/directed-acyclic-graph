/*
Seth Tal
01/26/2020
Assignment02 ~ Find longest path in Directed Acyclic Graph and number of longest paths of same length
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_FILENAME_LEN 14


void usage(int argc, char** argv) {
    if (argc < 3 || argc > 3) {
        fprintf(stderr, "usage: %s <input> <output>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

/* Node Struct
 * A Node contains a value and a list of its neighbors
*/
typedef struct Node {
    int val;          // value of current node
    struct Node* neighbors;  // list of node's neighbors
    int color;  // 0: unvisited, 1: visited
} Node;

/* Edge Struct
 * An edge contains two values representing starting node and ending node
*/
typedef struct Edge {
    Node* start;  // Start of edge
    Node* end;    // End of edge
    int w;        // weight of edge between start -> end
} Edge;

/* Graph Struct
 * A Graph G = {V, E} where |V| is a set of vertices (nodes) and |E| is a set of edges
*/
typedef struct Graph {
    Edge* adj;
} Graph;

// Todo: create malloc for node
void Malloc_Node();

// Todo: create malloc for edge
void Malloc_Edge();

// Todo: malloc the graph 
void Malloc_Graph(int n, int m, int* start, int* end, int* weight, Graph* g) {
    // Malloc the graph
    g = malloc(sizeof(Graph));

    g->adj = malloc(sizeof(Edge) * m);

    for (int i = 0; i < m; i++) {
        g->adj[i].start = malloc(sizeof(Node));
        g->adj[i].end = malloc(sizeof(Node));
    }
}

void Read_Matrix_Data(int *n, int *m, int** start, int** end, int** weight, FILE** input) {
    /* First line of the file contains two numbers N, and M
       * N : number of nodes
       * M : number of edges
    */
    fscanf(*input, "%d %d", n, m);

    /* Now I malloc the arrays passed into Read_Matrix_Data
       * start : a list of the starting nodes for a given edge
       * end : a list of the end node for a given edge
       * weight : a list of weights for a given edge
    */
    *start = (int *) malloc(sizeof(int) * *m);
    *end = (int *) malloc(sizeof(int) * *m);
    *weight = (int *) malloc(sizeof(int) * *m);

    // Assign values
    for (int i = 0; i < *m; i++) {
        fscanf(*input, "%d %d %d", &(*start)[i], &(*end)[i], &(*weight)[i]);
    }

    // ! TO BE REMOVED LATER:
    // printf("Grabbing graph data from stdin...\n");
    // printf(".\n");
    // printf(". N : %d\n. M : %d\n", *n, *m);
    // printf(".\n");
    // for (int j = 0; j < *m; j++)
    //     printf(". . %d -> %d . W : %d\n", (*start)[j], (*end)[j], (*weight)[j]);
    // printf(".\n");
    // printf(". Done\n");
    // printf("\n");
}

// ? T-Sort
void TopologicalSort();

// main is where the whole program executes
int main(int argc, char** argv) {    
    // function used to define usage of program
    usage(argc, argv); 

    int name_len = strlen(argv[1]);  // gets length of input file 1

    if (name_len > MAX_FILENAME_LEN) {
        fprintf(stderr, "Input file <%s> contains too many characters. Max length allowed is : %d\n", argv[1], MAX_FILENAME_LEN);
        exit(EXIT_FAILURE);
    }

    char matrix_name[MAX_FILENAME_LEN];  // init char *
    strcpy(matrix_name, argv[1]);        // copies over file_name to a char*

    int n;             // Number of Nodes
    int m;             // Number of Edges
    int* start_nodes;  // list of starting nodes
    int* end_nodes;    // list of ending nodes
    int* weight;       // weight of edge from start_nodes[i] -> end_nodes[i]
    int lp = 0;        // longest path represented by summation of total weight
    int num_lp = 0;    // number of paths that match this weight

    /* ----------------------------------------------------------------------------------------- */
    // Beginning stdout stream ... 
    printf("\n");
    fprintf(stdout, "Beginning read of Matrix : <%s> ... \n", matrix_name);

    // Todo: using file/io read in data from input file and store in some arr

    // ! start_nodes = malloc(sizeof(int) * m);
    // ! end_nodes = malloc(sizeof(int) * m);
    // ! weight = malloc(sizeof(int) * m);

    FILE* input = fopen(argv[1], "r");  // Opens input file for read only

    if (input == NULL) {
        fprintf(stderr, "ERR: could not open file <%s>\n", matrix_name);
        exit(EXIT_FAILURE);
    }

    Read_Matrix_Data(&n, &m, &start_nodes, &end_nodes, &weight, &input);

    assert(start_nodes);
    assert(end_nodes);
    assert(weight);

    fclose(input);

    // Todo: malloc necessary items from the arr to the 'graph'

    Graph* g;
    Malloc_Graph(n, m, start_nodes, end_nodes, weight, g);

    //Todo: stuff ...

    // End of stout stream.
    /* ----------------------------------------------------------------------------------------- */
    printf("\n");

    // ! FREE anything malloc'd bellow...
    free(start_nodes);
    free(end_nodes);
    free(weight);
    free(g);

    return 0;
}
