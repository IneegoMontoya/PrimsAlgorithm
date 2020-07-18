#include "header.h"


/*
written by Byron Smith, Dylan Bunch, and Ben Blanquart

	compile with gcc main.c source.c
	
	note the input file has to be named input.txt
	This algorithm reads in a file in the openfile function.
	It then converts that list into an array of vertexes.
	Afterwards it converts the edges linked list into an array.
	After converting the edge list into an array, we add the adjacent edges into each vertex's adjacentEdges pointer.
	Using these data structures we then create 3 arrays. One is a heap, the others keep track of the vertex's key and position on the heap.
	After creating these arrays, we pass them to MSTPrim's which calculates the total MST weight.
*/

int main(void){
	
	//read in the file
	edge* initialEdgeList = openfile("input.txt");

	//print the resulting list
	//printEdgeList(initialEdgeList);

	//translate that list into an array of vertices and prints them
	vertex* initialVertexArray = createVertexList(initialEdgeList);

	//converts the edge list into an edge array
	edge* edgeArray = convertToEdgeArray(initialEdgeList);
	

	//add adjacent edges to the vertex list for more information
	addAdjacentEdges(initialVertexArray, edgeArray);

	//prsint the adjacency list (i.e. vertex array and its adjacency list pointer)
	//printAdjacencies(initialVertexArray);

	//sort adjacencies by edge weight
	sortAdjacencies(initialVertexArray);

	//print sorted adjacencies
	//printAdjacencies(initialVertexArray);

	//create an array of integers that correspond with the vertices in the graph
	int* minHeap = createHeap(initialVertexArray); 

	//an array of integers that correspond to the vertices' keys
	int* heapKeys = createKeyArray(initialVertexArray);

	//an array of integers that correspond to the vertices position on the heapArray
	int* onHeap = createOnHeapArray(initialVertexArray);

	//simple helper function to remove clutter from main and print the heap for debugging
	//printHeap(minHeap, onHeap, heapKeys);

	//the actual algorithm gets called for these data structures
	mstPrims(minHeap, onHeap, heapKeys, initialVertexArray);


	memCleanup(minHeap, heapKeys, onHeap, initialEdgeList, edgeArray, initialVertexArray);
	
	return 0;
}