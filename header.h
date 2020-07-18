#include <stdio.h>
#include <stdlib.h>

#define left(x) (2*x)+1 // defines where the "left" child node should be
#define right(x) (2*x)+2 // defines where the "right" chile node should be
#define parent(x) (x-1)/2  // defines where to find the parent of a given element

typedef struct vertex{
	int key;
	struct adjacentEdge* adjacentEdges;
}vertex;

typedef struct edge{
	struct vertex u;
	struct vertex v;
	int w;
	struct edge* next;
}edge;

typedef struct adjacentEdge{
	vertex v;
	int w;
	struct adjacentEdge* next;
}adjacentEdge;

edge* openfile(char*);
void printEdgeList(edge*);
vertex* createVertexList(edge*);
edge* convertToEdgeArray(edge*);
void printEdgeArray(edge*);
void addAdjacentEdges(vertex*,edge*);
vertex* addAdjacentEdge(vertex*,int,vertex,int);
void printAdjacencies(vertex*);
void sortAdjacencies(vertex*);
int* createHeap(vertex*);
int* createKeyArray(vertex*);
int* createOnHeapArray(vertex*);
int extractMin(int*,int*,int*);
void heapify(int*,int*,int*,int);
void swap(int*,int*);
void mstPrims(int*,int*,int*,vertex*);
void decreaseKey(int*,int*,int*,int,int);
void printHeap(int*,int*,int*);
void memCleanup(int*,int*,int*,edge*,edge*,vertex*);