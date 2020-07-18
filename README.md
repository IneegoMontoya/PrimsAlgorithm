# PrimsAlgorithm
Implementation of Prim's Algorithm done in C. Group project completed for CS3050 at the University of Missouri - Columbia. 

written by Byron Smith, Dylan Bunch, and Ben Blanquart

	compile with gcc main.c source.c
	
	note the input file has to be named input.txt
	This algorithm reads in a file in the openfile function.
	It then converts that list into an array of vertexes.
	Afterwards it converts the edges linked list into an array.
	After converting the edge list into an array, we add the adjacent edges into each vertex's adjacentEdges pointer.
	Using these data structures we then create 3 arrays. One is a heap, the others keep track of the vertex's key and position on the heap.
	After creating these arrays, we pass them to MSTPrim's which calculates the total MST weight.
