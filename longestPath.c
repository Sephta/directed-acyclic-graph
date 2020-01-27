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

// Todo: T-Sort
void TopologicalSort();

int main(int argc, char** argv) {    
    // function used to define usage of program
    usage(argc, argv); 

    int name_len = strlen(argv[1]);  // gets length of input file 1

    if (name_len > MAX_FILENAME_LEN) {
        fprintf(stderr, "Input file <%s> contains too many characters. Max length allowed is : %d\n", argv[1], MAX_FILENAME_LEN);
        exit(EXIT_FAILURE);
    }

    char matrix_name[MAX_FILENAME_LEN];  // init char *
    strcpy(matrix_name, argv[1]);         // copies over file_name to a char*

    
    /* ----------------------------------------------------------------------------------------- */
    // Beginning stdout stream ... 
    printf("\n");
    fprintf(stdout, "Beginning read of Matrix : <%s> ... \n", matrix_name);

    // Todo: stuff ... 

    printf("\n");
    return 0;
}
