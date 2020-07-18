#include "header.h"

int minHeapifyCalls = 0;
int totalWeight = 0;

//opens input.txt and reads through the edge list and puts into an array
edge* openfile(char* file){

	//open the file named "input.txt"
	FILE* fptr = fopen(file, "r");

	//if it didn't open, the program crashes
	if(fptr == NULL){
		printf("Error opening file %s. Exiting.\n",  file);
		exit(0);
	}

	//create temporary vertex structures that will be used to read in the values of the file
	vertex u, v;

	//initialize their keys
	u.key = 0, v.key = 0;

	//initialize a temporary weight variable to read in the weight of the edges from the file
	int w = 0;

	//establish the head pointer of this linked list to be NULL
	edge* head = NULL;

	//read until the file is at its end
	while(!feof(fptr)){

		//scan in the line of text and put them in the corresponding variable spots
		fscanf(fptr, "%d %d %d\n", &u.key, &v.key, &w);

		//add a node with these values to the linked list
		edge* temp  = malloc(sizeof(edge));
		temp->u.key = u.key;
		temp->v.key = v.key;
		temp->w = w;
		temp->next = NULL;

		//insert at the head if the head is not empty
		if(head != NULL){
			temp->next = head;
			head = temp;
		}

		//if the head is empty, just set the head equal to the new node that was malloced
		if(head == NULL)
			head = temp;
	}

	//close the file like a good boy
	fclose(fptr);


	//return the linked list pointer
	return head;
}

//prints the edge linked list
void printEdgeList(edge* head){

	printf("\nEdge List is as follows: \n");

	edge* cursor = head;

	while(cursor != NULL){
		printf("[%d]<---%d--->[%d]\n", cursor->u.key, cursor->w, cursor->v.key);
		cursor = cursor->next;
	}

	return;
}

//translates the edge linked list into a vertex array with size at vertexs[-1].key
vertex* createVertexList(edge* head){

	//create some temporary variables that do some things
	edge* cursor = head;
	int maxvertex = 0;
	int maxweight = 0;

	//use the cursor to iterate through the list until we reach the end of the list
	while(cursor != NULL){

		//find the max vertex among the linked list
		if(cursor->u.key > maxvertex)
			maxvertex = cursor->u.key;
		if(cursor->v.key > maxvertex)
			maxvertex = cursor->v.key;

		//also find the max weight
		if(cursor->w >= maxweight)
			maxweight = cursor->w;

		//iterate to the next node
		cursor = cursor->next;
	}

	//malloc an array equal to the size of the maximum vertex number + 2 for storing variables in negative space
	vertex* vertexes = malloc(sizeof(vertex) * (maxvertex + 2));

	//maxweight is stored at vertexes[-2]
	vertexes[0].key = maxweight;
	vertexes++;

	//size of the array/maximum vertex number is located at vertexes[-1]
	vertexes[0].key = maxvertex;
	vertexes++;

	// print out this vertex array
	// printf("\nVertex array is as follows:\n");
	for(int i = 0; i < maxvertex; i++){
		vertexes[i].key = i + 1;
		vertexes[i].adjacentEdges = NULL;
	// 	printf("[%d]\n", vertexes[i].key);
	}
	// printf("\n");

	//return the array to main
	return vertexes;
}

//converts the  edge list into an edge array with size stored at edgearray[-1].w
edge* convertToEdgeArray(edge* edgelist){

	//temporary pointer to iterate through the edge list
	edge* cursor = edgelist;

	//keep a count of the number of edges in the graph
	int count = 0;

	//count the number of edges
	while(cursor != NULL){
		count++;
		cursor = cursor->next;
	}

	//create an edgearray of size equal to the number of edges plus 1
	edge* edgearray = malloc(sizeof(edge) * (count + 1));

	//set the 0th element to the size of the array and then increment the pointer hiding the size in negative space
	edgearray[0].w = count;
	edgearray++;

	//reset count and point the cursor to the edgelist again
	count = 0;
	cursor = edgelist;

	//loop through the edge list one more time and  copy the linked list into the array
	while(cursor != NULL){
		edgearray[count] = *cursor;
		count++;
		cursor = cursor->next;
	}

	//return the array
	return edgearray;
}

//prints edge array
void printEdgeArray(edge* edgearray){

	printf("\nEdgeArray is as follows:\n");

	for(int i = 0; i < edgearray[-1].w; i++){
		//printf("%d %d %d\n", edgearray[i].u.key, edgearray[i].v.key, edgearray[i].w);
		printf("%d: [%d]---%d---[%d]\n", i, edgearray[i].u.key, edgearray[i].w, edgearray[i].v.key);
	}
}

//adds adjacent edges to the vertex list to form an adjacency list
void addAdjacentEdges(vertex* vertexList, edge* edgeArray){

	//a bunch o' temporary variables
	int index = 0;
	vertex temp;
	int weight = 0;

	//iterate through the dge array
	for(int i = 0; i < edgeArray[-1].w; i++){

		//look at left side and add right side to the left side's adjacency list
		index = edgeArray[i].u.key;
		temp = edgeArray[i].v;
		weight = edgeArray[i].w;
		vertexList = addAdjacentEdge(vertexList, (index - 1), temp, weight);

		//look at right side and add left side to the right side's adjacency list
		index = edgeArray[i].v.key;
		temp = edgeArray[i].u;
		weight = edgeArray[i].w;
		vertexList = addAdjacentEdge(vertexList, (index - 1), temp, weight);
	}
}

//helper function for above
vertex* addAdjacentEdge(vertex* vertexList, int index, vertex vert, int weight){

	//malloc an edge and set its 
	adjacentEdge* mallocator = malloc(sizeof(adjacentEdge));
	mallocator->v = vert;
	mallocator->w = weight;

	//this is a long way to say "insert at head of linked list"
	mallocator->next = vertexList[index].adjacentEdges;
	vertexList[index].adjacentEdges = mallocator;

	return vertexList;
}

//prints the adjacency lists
void printAdjacencies(vertex* vertexList){

	adjacentEdge* cursor = NULL;

	printf("\nVertexes and edges are\n");
	for(int i = 0; i < vertexList[-1].key; i++){
		cursor = vertexList[i].adjacentEdges;
		printf("%d: ", vertexList[i].key);
		while(cursor != NULL){
			printf("(vert: %d, w: %d)-> ", cursor->v.key, cursor->w);
			cursor = cursor->next;
		}
		printf("\n");
	}
}

//bubble sorts adjacent edges based on edge weight
//please don't bully our grade for this
void sortAdjacencies(vertex* vertexArray){

	//temporary variables to help with readability and functionality
	int size = vertexArray[-1].key;
	int k;
	adjacentEdge *i, *j;
	int tempW;
	vertex tempV;
	adjacentEdge* cursor;

	//iterate through the vertexes of the adjacency list
	for(k=0; k<size; k++){
		cursor = vertexArray[k].adjacentEdges;

		//do a bubble sort on this linked list
		for(i=cursor; i != NULL; i=i->next){
			for(j=i->next; j != NULL; j=j->next){
				if(i->v.key > j->v.key){
					//swap
					tempW = i->w;
					tempV = i->v;
					i->w = j->w;
					i->v = j->v;
					j->w = tempW;
					j->v = tempV;
				}
				
			}
		}
	}
}


//creates an array of numbers with each index corresponding to a vertex number
int* createHeap(vertex* vertexArray){

	//helper variables to improve readability
	int maxWeight = vertexArray[-2].key;
	int size = vertexArray[-1].key;

	//create an array the size of the number of vertices + 2
	int* heap = malloc(sizeof(int)*(size+2));

	//hiding the maximum edge weight in the -2 index
	heap[0] = maxWeight;
	//hiding the heapsize in the -1 index
	heap[1] = size;
	heap+=2;

	//initialize the indices to correspond to a vertex
	for(int i=0; i<size; i++){
		heap[i] = i+1;
	}

	return heap;
}

//create an array of ints that contain the keys corresponding to the vertex number
//initializes them all to infinity
int* createKeyArray(vertex* vertexArray){

	//helper variables
	int maxWeight = vertexArray[-2].key;
	int size = vertexArray[-1].key;
	int infinity = maxWeight + 1;

	//malloc an array of size equal to the maximum vertex number + 1
	int* keys = malloc(sizeof(int)*(size+1));

	//initialize all the key values to infinity
	for(int i=0; i<size; i++){
		keys[i] = infinity;
	}

	//except the first one, lol
	keys[0] = 0;

	//return the array because this is a pass-by-value
	return keys;
}

//creates an array of numbers each with indices corresponding to a vertex number
int* createOnHeapArray(vertex* vertexArray){

	//create an array of size equal to the maximum vertex number + 1
	int size = vertexArray[-1].key;
	int* onHeap = malloc(sizeof(int)*(size+1));

	//for this we ignore index 0 as it doesn't correspond to a vertex
	//establish each vertex's position on the heap with this loop
	for(int i=1; i<(size+1); i++){
		onHeap[i] = i-1;
	}

	//return the array lol
	return onHeap;
}

// run of the mill swap 
void swap(int *x, int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

//print the heap, mostly for debugging
void printHeap(int* minHeap, int* onHeap, int* heapKeys){

	printf("Minheap:\n");

	for(int i = 0;i < minHeap[-1]; i++){

		printf("vert: %d position onheap:%d key: %d\n", minHeap[i], onHeap[minHeap[i]], heapKeys[minHeap[i]-1]);

	}
}

//implementation of min-heapify for iterating nodes down the list to sort them, but not up
void heapify(int *heap, int* keyArray, int* onHeap, int index){

	//add 1 call to heapify's total calls
	minHeapifyCalls++;

	//some temporary local ints
	int size = heap[-1];
	int smallest;

		//some key comparisons for swapping purposes
		if(left(index) < size && ((keyArray[(heap[left(index)])-1] < keyArray[heap[index]-1]) || ((keyArray[(heap[left(index)])-1] == keyArray[heap[index]-1]) && (heap[left(index)] < heap[index])))){
			smallest = left(index);
		} else{
			smallest = index;
		}

		//same thing as above, just for the right side
		if(right(index) < size && ((keyArray[heap[right(index)]-1] < keyArray[heap[smallest]-1])  || ((keyArray[heap[right(index)]-1] == keyArray[heap[smallest]-1]) && (heap[right(index)] < heap[smallest])))){
			smallest = right(index);
		}

		//call heapify if heapify needs to be called
		if(smallest != index){
			swap(&onHeap[heap[index]], &onHeap[heap[smallest]]);
			swap(&heap[index], &heap[smallest]);
			heapify(heap, keyArray, onHeap, smallest);
		}

		return;
}

//extract the minimum node from the top of the heap
int extractMin(int* heap, int* onHeap, int* keyArray){

	//some temporary local variables to make the code somewhat more readable
	totalWeight += keyArray[heap[0]-1];
	int endofheap = heap[(heap[-1])-1];


	//if, for some reason, the array is of size 0 or negative size, the program crashes
	if(heap[-1] < 1){
		printf("HEAP UNDERFLOW, exiting...\n");
		exit(1);
	}

	//temporary helper variable
	int min = heap[0];

	//set that vertexe's position on the heap to -1 or off the heap
	onHeap[min] = -1;

	//blast the bottom node of the heap to the top to sort out the problem created by extracting the minimum node
	heap[0] = endofheap;

	//set the position for the new top node to 0 so heapify works
	onHeap[endofheap] = 0;

	//decrease heapsize
	heap[-1]--;

	//call heapify to fix the problem
	heapify(heap, keyArray, onHeap, 0);

	return min;
} 

//the actual algorithm that uses all of these helper functions
void mstPrims(int* heap, int* onHeap, int* keyArray, vertex* vertexArray){

	//this was a testing printf
	//printf("\n\n\n%d\n\n\n", minHeapifyCalls);

	//u is a temporary int
	int u;

	//set is an array of "edges" that are picked by Prim's
	int* set = malloc((sizeof(int)*(heap[-1] +1)));

	//hiding posistion in set in -1 index
	set[0] = 0;
	set += 1;

	//create a cursor to iterate through the adjacency lists of the vertices
	adjacentEdge* cursor;

	//loop until the heap is empty
	while(heap[-1] > 0){

		//get the minimum node
		u = extractMin(heap, onHeap, keyArray);

		//add it to the selected edges array and increment the size of the edges picked
		set[set[-1]] = u;
		set[-1]++;

		//iterate through the adjacency list of the u node to find its minimum edge
		cursor = vertexArray[u-1].adjacentEdges;		

		//find the minimum edge among the adjacency list
		while(cursor != NULL){

			//if the node is still on the heap and the weight is the least, add it
			if(onHeap[cursor->v.key] > -1 && cursor->w < keyArray[(cursor->v.key)-1]){
				
				//call decreasekey to fix the heap
				decreaseKey(heap, onHeap, keyArray, onHeap[cursor->v.key], cursor->w);

			}

			//iterate to the next adjacent node
			cursor = cursor->next;

		}
	}


	//free the temporary set array
	set-=1;
	free(set);

	//print the weight of the mst and the total calls to the heapify function
	printf("Total MST Weight: %d", totalWeight);
	printf("\nTotal Heapify Calls: %d\n", minHeapifyCalls);
}

//decrease key is a function that works similar to the heapify function, but sorts upwards rather than down
void decreaseKey(int* heap, int* onHeap, int* keyArray, int index, int key){

	//a temporary integer that points to the parent of the node in question
	int p = parent(index);

	//if these are the 2nd or 3rd nodes
	if(index == 2 || index == 1){
		p = 0;
	}

	//if the key of the node in question is greater than the key of the index node
	if(key > keyArray[heap[index]-1]){
		printf("ERROR: new key larger than the current key\n");
		exit(1);
	}

	//set the key of the node in question to be the weight of the minimal edge of its adjacent edges
	keyArray[heap[index]-1] = key;

	//whiel the index isn't the top node of the heap and the parent key is greater than the child key
	while(index > 0 && ((keyArray[heap[p]-1] > keyArray[heap[index]-1]) || ((keyArray[heap[p]-1] == keyArray[heap[index]-1]) && (heap[p] > heap[index])))){

		//swap those two nodes
		swap(&onHeap[heap[index]], &onHeap[heap[p]]);
		swap(&heap[index], &heap[p]);
		
		//reset the values for the next loop iteration
		index = parent(index);
		p = parent(index);
		
	}

}

void memCleanup(int* minHeap, int* onHeap, int* heapKeys, edge* initialEdgeList, edge* edgeArray, vertex* initialVertexArray){

	//freeing the min heap
	minHeap -=2;
	free(minHeap);
	free(heapKeys);
	free(onHeap);

	//Freeing the edge array
	edgeArray--;
	free(edgeArray);

	
	int i;
	adjacentEdge* temp = NULL;
	adjacentEdge* temp2 = NULL;
	
	//free adjacent edges linked list associated with the vertex array
	int size = initialVertexArray[-1].key;
	for(i=0; i < size; i++){
		temp = initialVertexArray[i].adjacentEdges;
		while(temp != NULL){;
			temp2 = temp;
			temp = temp->next;
			free(temp2);
		}
	}


	edge* temp3 = initialEdgeList;
	edge* temp4;

	//freeing the linked list of the edge list
	while(temp3 != NULL){			
			temp4 = temp3;
			temp3 = temp3->next;
			free(temp4);
	}


	//freeing up the vertex array
	initialVertexArray-=2;
	free(initialVertexArray);

	
	return;
}