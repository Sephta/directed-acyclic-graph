/*
Seth Tal
01/26/2020
Assignment02 ~ Find longest path in Directed Acyclic Graph and number of longest paths of same length

Acknowledgements / Credit:
I received assistance through discussion from the following people...
> Zhangxiang Hu
> Abduarraheem Elfandi

The only outside recourses used to complete this project are class notes and lecture slides from the website
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
    int w;    // if node is a predecessor then w represents weight of edge from sucessor -> node
} Node;

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
            (*p)[i][j].w = 0;
        }
    }
}

void Free_P_Tree(int n, Node** p) {
    for (int i = 0; i < n; i++) {
        Node* current_ptr = p[i];
        free(current_ptr);
    }
}

/*
 * This function simply initializes the adjaceny matrix defined in main()
*/
void Build_P_Tree(int n, int m, int* start, int* end, int* weight, Node** p) {
    for (int i = 0; i < m; i++) {
        // This is a small optimization such that the calculation does not need to be calculated when compiled 3n times
        int curr_node = end[i] - 1;
        for (int j = 0; j < n; j++) {
            if (p[curr_node][j].val == -1) {
                p[curr_node][j].val = start[i];
                p[curr_node][j].w = weight[i];
                break;
            }
        }
    }
}

/*
 * i = current node
 * j = current predecessor
 * w = weight
 * val = node value
 * lp[i] = longest path of i'th node
 * nlp[i] = number of longest paths to i'th node
*/
void Process_P_Tree(int n, int m, int* lp, int* nlp, Node** p) {
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

/*
 * This function reads the data from stdin and stores into arrays
*/
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
}

/*
 * main is where the whole program executes
*/ 
int main() {

    // function used to define usage of program
    int n;             // Number of Nodes
    int m;             // Number of Edges
    int* start_nodes;  // list of starting nodes
    int* end_nodes;    // list of ending nodes
    int* weight;       // weight of edge from start_nodes[i] -> end_nodes[i]

    int* lp_arr;       // longest path array. Each index corresponds to a node on the graph. The i'th node corresponds to the i'th index of the array
    int* num_lp_arr;   // Same logic as above.
    Node** p_tree;     // the adjacency list I built is a literal matrix

    /*
    */

    /* ----------------------------------------------------------------------------------------- */
    // Beginning stdout stream ... 

    Read_Matrix_Data(&n, &m, &start_nodes, &end_nodes, &weight);

    assert(start_nodes);
    assert(end_nodes);
    assert(weight);

    /* ------------------------------------------- */
    lp_arr = malloc(sizeof(int) * n);
    num_lp_arr = malloc(sizeof(int) * n);

    // Initialize the longest path array and num longest path arrays
    for (int i = 0; i < n; i++) {
        // The starting node will always initialize to lp[0] = 0, nlp[0] = 1
        if (i == 0) {
            lp_arr[i] = 0;
            num_lp_arr[i] = 1;
        } else {
            lp_arr[i] = BIG_NEGATIVE_NUMBER;
            num_lp_arr[i] = 0;
        }
    }

    Malloc_P_Tree(n, &p_tree);

    // Here is where I simply build my adjacency list
    Build_P_Tree(n, m, start_nodes, end_nodes, weight, p_tree);

    // This is where I implemented a longest path algorithm
    Process_P_Tree(n, m, lp_arr, num_lp_arr, p_tree);

    fprintf(stdout, "longest path: %d\nnumber of longest paths: %d\n", lp_arr[n-1], num_lp_arr[n-1]);

    // End of stout stream.
    /* ----------------------------------------------------------------------------------------- */

    // Here I free any and all malloc'd data bellow...
    free(start_nodes);
    free(end_nodes);
    free(weight);

    Free_P_Tree(n, p_tree);
    free(p_tree);

    free(lp_arr);
    free(num_lp_arr);

    return 0;
}
