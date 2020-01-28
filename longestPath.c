/*
Seth Tal
01/26/2020
Intermediate Algorithms (CIS 315): Assignment02

Find longest path in Directed Acyclic Graph and number of longest paths of same length.
Graph is given in a txt file...

Top of file has two numbers N and M. 
N -> number of nodes in the graph
M -> number of edges

Each line following contains three numbers I, J, W together representing an edge.

I -> starting node of edge
J -> ending node of edge
W -> weight of edge

This version of the program is the version I will utilize on GitHub, whereas longestPath2.c is the
version I submitted to the course for grading.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_FILENAME_LEN 14
#define BIG_NEGATIVE_NUMBER -2147483640


void usage(int argc, char** argv) {
    if (argc < 3 || argc > 3) {
        fprintf(stderr, "usage: %s <input> <output>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

/* Node Struct
 * A Node contains a value denoting which node it is in the graph, and two ints
 * int val : node value
 * int lp : current longest path to node from predecessors by weight
 * int nlp : number of longest paths to node
 * int w : when contained within the predecessor tree, a nodes weight is the weight of the edge from the node's sucessor
*/
typedef struct Node {
    int val;  // value of current node
    int lp;   // current longest path value (by weight)
    int nlp;  // current number of longest paths
    int w;    // if node is a predecessor then w represents weight of edge from sucessor -> node
    // struct Node* next;
} Node;

// Todo: add comments
void Malloc_P_Tree(int n, Node*** p) {
    // malloc the predecessor node array
    
    *p = (Node **) malloc(sizeof(Node *) * n);

    for (int i = 0; i < n; i++) {
        (*p)[i] = malloc(sizeof(Node) * n);
        for (int j = 0; j < n; j++) {
            if (j == 0)
                (*p)[i][j].val = i + 1;
            else
                (*p)[i][j].val = -1;

            if (i == 0 && j == 0)
                (*p)[i][j].lp = 0;
            else
                (*p)[i][j].lp = BIG_NEGATIVE_NUMBER;

            (*p)[i][j].nlp = 1;
            (*p)[i][j].w = 0;
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         printf(" %d ", p[i][j].val);
    //     }
    //     printf("\n");
    // }
}

// Todo: add comments
void Build_P_Tree(int n, int m, int* start, int* end, int* weight, Node** p) {
    // int next_pred = 1;
    for (int i = 0; i < m; i++) {
        int curr_node = end[i] - 1;
        for (int j = 0; j < n; j++) {
            if (p[curr_node][j].val == -1) {
                p[curr_node][j].val = start[i];
                p[curr_node][j].w = weight[i];
                break;
            }
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         printf(" %d ", p[i][j].val);
    //     }
    //     printf("\n");
    // }
}

// Todo: add comments
void Process_P_Tree(int n, int m, int* lp, int* nlp, Node** p) {
    /*
     * i = current node
     * j = current predecessor
     * w = weight
     * val = node value
     * lp[i] = longest path of i'th node
     * nlp[i] = number of longest paths to i'th node
    */

    // from node 1 till node n
    for (int i = 0; i < n; i++) {
        // from predecessor 1 till n
        for (int j = 1; j < n; j++) {
            // if curr_pred value == -1 then no more predecessors
            if (p[i][j].val == -1)
                break;
            else {
                // (curr_pred.w + prev_node's lp > curr_node's lp)
                if (p[i][j].w + lp[p[i][j].val - 1] > lp[i]) {
                    // curr_node's lp = curr_pred.w + prev_nodes's lp
                    lp[i] = p[i][j].w + lp[p[i][j].val - 1];
                    // curr_nlp = previous nlp
                    nlp[i] = nlp[p[i][j].val - 1];
                }
                // curr_pred.w + prev_node's lp == curr_node's lp
                else if (p[i][j].w + lp[(p[i][j].val) - 1] == lp[i]){
                    // curr_nlp += prev_nlp
                    nlp[i] += nlp[i - 1];
                }
            }
        }
    }
}

// Todo: add comments
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

// main is where the whole program executes
// Todo: add comments
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

    int* lp_arr;           // longest path array. Each index corresponds to a node on the graph. The i'th node corresponds to the i'th index of the array
    int* num_lp_arr;          // Same logic as above.
    Node** p_tree;

/* --------------------------------------------------------------------------------------------- */
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

    // printf("Grabbing graph data from stdin...\n");
    // printf(".\n");
    // printf(". N : %d\n. M : %d\n", n, m);
    // printf(".\n");
    // for (int j = 0; j < m; j++)
    //     printf(". . %d -> %d . W : %d\n", start_nodes[j], end_nodes[j], weight[j]);
    // printf(".\n");
    // printf(". Done\n");
    // printf("\n");

    assert(start_nodes);
    assert(end_nodes);
    assert(weight);

    fclose(input);

/* ------------------------------------------- */
    lp_arr = malloc(sizeof(int) * n);
    num_lp_arr = malloc(sizeof(int) * n);

    // Initialize all values in lp_arr to 0 and num_lp_arr to 1
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            lp_arr[i] = 0;
            num_lp_arr[i] = 1;
        } else {
            lp_arr[i] = BIG_NEGATIVE_NUMBER;
            num_lp_arr[i] = 0;
        }
    }

    Malloc_P_Tree(n, &p_tree);

    Build_P_Tree(n, m, start_nodes, end_nodes, weight, p_tree);

    Process_P_Tree(n, m, lp_arr, num_lp_arr, p_tree);

    printf("lp  : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", lp_arr[i]);
    }
    printf("\n");

    printf("nlp : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", num_lp_arr[i]);
    }
    printf("\n");

/* ------------------------------------------- */

    // Writing answer to output file specified in arg 2 (argv[2])

    fprintf(stdout, "Writing answer to output file <%s> ... ", argv[2]);

    FILE* output = fopen(argv[2], "w");

    if (output == NULL){
        fprintf(stderr, "\nERR: could not open file <%s>\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    
    fprintf(output, "longest path: %d\nnumber of longest paths: %d\n", lp_arr[n-1], num_lp_arr[n-1]);

    fclose(output);
    fprintf(stdout, "Done\n");

    // End of stdout stream.
/* --------------------------------------------------------------------------------------------- */
    printf("\n");

    // ! FREE anything malloc'd bellow...
    free(start_nodes);
    free(end_nodes);
    free(weight);

    free(lp_arr);
    free(num_lp_arr);
    free(p_tree);

    return 0;
}
