/*
Seth Tal
01/26/2020
Assignment02 ~ Find longest path in Directed Acyclic Graph and number of longest paths of same length
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void usage(int argc, char** argv) {
    if (argc < 3 || argc > 3) {
        fprintf(stderr, "usage: %s <input> <output>\n", argv[0]);
    }
}

// Todo: T-Sort
void TopologicalSort();

int main(int argc, char** argv) {    
    usage(argc, argv);

    // Todo: Stuff

    return 0;
}
