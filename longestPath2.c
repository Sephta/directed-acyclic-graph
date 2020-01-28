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
#define BIG_NEGATIVE_NUMBER -2147483640


/* Node Struct
 * A Node contains a value and a list of its neighbors
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
    
    for (int i = 0; i < n; i++) {
        // printf("Node(%d) ~ ", i + 1);
        for (int j = 1; j < n; j++) {
            if (p[i][j].val == -1)
                break;
            else {

                if (p[i][j].w + lp[p[i][j].val - 1] > lp[i]) {
                    lp[i] = p[i][j].w + lp[p[i][j].val - 1];
                    nlp[i] = nlp[i - 1];
                } else if (p[i][j].w + lp[p[i][j].val - 1] == lp[i])
                    nlp[i] += nlp[i-1];
                // printf("lp : %d\n", lp[i]);
            }
        }
        // printf("\n");
    }
}

// Todo: Read in data from input file ...
void Read_Matrix_Data(int *n, int *m, int** start, int** end, int** weight) {
    /* First line of the file contains two numbers N, and M
       * N : number of nodes
       * M : number of edges
    */
    fscanf(stdin, "%d %d", n, m);

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
        fscanf(stdin, "%d %d %d", &(*start)[i], &(*end)[i], &(*weight)[i]);
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
int main() {    
    // function used to define usage of program

    int n;             // Number of Nodes
    int m;             // Number of Edges
    int* start_nodes;  // list of starting nodes
    int* end_nodes;    // list of ending nodes
    int* weight;       // weight of edge from start_nodes[i] -> end_nodes[i]

    int* lp_arr;           // longest path array. Each index corresponds to a node on the graph. The i'th node corresponds to the i'th index of the array
    int* num_lp_arr;          // Same logic as above.
    Node** p_tree;

    /* ----------------------------------------------------------------------------------------- */
    // Beginning stdout stream ... 
    printf("\n");

    Read_Matrix_Data(&n, &m, &start_nodes, &end_nodes, &weight);

    assert(start_nodes);
    assert(end_nodes);
    assert(weight);

    /* ------------------------------------------- */
    lp_arr = malloc(sizeof(int) * n);
    num_lp_arr = malloc(sizeof(int) * n);

    // Initialize all values in lp_arr to 0 and num_lp_arr to 1
    for (int i = 0; i < n; i++) {
        lp_arr[i] = 0;
        num_lp_arr[i] = 1;
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

    fprintf(stdout, "longest path: %d\nnumber of longest paths: %d\n", lp_arr[n-1], num_lp_arr[n-1]);

    // End of stout stream.
    /* ----------------------------------------------------------------------------------------- */
    printf("\n");

    // ! FREE anything malloc'd bellow...
    free(start_nodes);
    free(end_nodes);
    free(weight);

    return 0;
}
