#pragma once
#include <iostream>
#include "Stack.h"
#include "Vector.h"

class Graphs {
public:
	Vector* mainList;

	int currentSize;
	int nrOfGraphs;

	Graphs();

	void merge(int array[], int low, int middle, int high, bool flag);
	void mergeSort(int array[], int low, int high, bool flag);

	void degreeSequence();
	void complementsEdges();

	void DFS(int start, bool visited[]);
	void numberOfSequences();

	void bipartiteness();

	void verticesColoring(bool flag);

	void mainLoop();
};