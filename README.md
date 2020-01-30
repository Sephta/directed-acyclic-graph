Seth Tal

01/26/2020

Intermediate Algorithms (CIS 315): Assignment02 @ University of Oregon

# Longest Path & Number of Longest Paths
Program that prints longest path and number of longest paths in a given directed acyclic graph to an output file.
The input files organize the edges in Topologically sorted order and provide weights to each edge.

Graph is represented in a .txt file...

The top of the input sample files have two numbers N and M. 
    
    N -> number of nodes in the graph
    
    M -> number of edges

Each line following contains three numbers I, J, W together representing an edge.
    
    I -> starting node of edge
    
    J -> ending node of edge
    
    W -> weight of edge
    
Provided to me for this project where two example input files called 'inSample1.txt' and 'inSample2.txt'.
These contain the given data about a graph as described above.

# How to run the program

In a unix environment or oporating system open the directory this program is located in using any shell/terminal.
Make sure gcc is installed as that is what I use as my C compiler. I technically used the -std=c11 flag when compiling
but simply running the commands bellow should achieve the same result.

```bash
gcc longestPath.c
./a.out inSample1.txt output.txt
```
or
```bash
gcc longestPath2.c
./a.out < inSample1.txt
```
