#define _CRT_SECURE_NO_WARNINGS
#include "Graphs.h"

#define NONE -5
#define A 1
#define B -1

Graphs::Graphs() : mainList(), currentSize(0), nrOfGraphs(0) {};

void Graphs::merge(int array[], int low, int middle, int high, bool flag=false) {
    int n1 = middle - low + 1;
    int n2 = high - middle;

    int* left = new int[n1];
    int* right = new int[n2];

    for (int i = 0; i < n1; i++) 
        left[i] = array[low + i];
    
    for (int i = 0; i < n2; i++) 
        right[i] = array[middle + 1 + i];
    

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (flag) {
            if (mainList[left[i]].getSize() > mainList[right[j]].getSize() || 
                (mainList[left[i]].getSize() == mainList[right[j]].getSize() && left[i] < right[j])) {
                array[k] = left[i];
                i++;
            }
            else {
                array[k] = right[j];
                j++;
            }
            k++;
        }
        else {
            if (left[i] <= right[j]) {
                array[k] = left[i];
                i++;
            }
            else {
                array[k] = right[j];
                j++;
            }
            k++;
        }
    }

    while (i < n1) {
        array[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = right[j];
        j++;
        k++;
    }

    delete[] left;
    delete[] right;
}

void Graphs::mergeSort(int array[], int low, int high, bool flag = false) {
    if (low < high) {
        int middle = low + (high - low) / 2;
        mergeSort(array, low, middle, flag);
        mergeSort(array, middle + 1, high, flag);
        merge(array, low, middle, high, flag);
    }
}

void Graphs::degreeSequence() {
    int* temp = new int[currentSize];

    for (int i = 0; i < currentSize; i++) 
        temp[i] = mainList[i].getSize();
    
    mergeSort(temp, 0, currentSize - 1);

    for (int i = currentSize - 1; i >= 0; i--) 
        printf("%d ", temp[i]);
    printf("\n");

    delete[] temp;
}

void Graphs::complementsEdges() {
    long long  count = 0;

    for (int i = 0; i < currentSize; i++) 
        count += mainList[i].getSize();
    

    long long temp1 = currentSize - 1;
    long long temp2 = temp1 * currentSize;
    long long res = (temp2 - count) / 2;
    printf("%lld\n", res);
}

void Graphs::DFS(int start, bool visited[]) {
    Stack stack;
    stack.push(start);

    while (!stack.isEmpty()) {
        int top = stack.pop();

        if (visited[top - 1]) 
            continue;
        
        visited[top - 1] = true;

        for (int i = 0; i < mainList[top - 1].getSize(); i++) 
            if (!visited[mainList[top - 1][i] - 1]) 
                stack.push(mainList[top - 1][i]);
    }
}

void Graphs::numberOfSequences() {
    bool* visited = new bool[currentSize];
    for (int i = 0; i < currentSize; i++) 
        visited[i] = false;
    

    int res = 0;
    for (int i = 0; i < currentSize; i++) 
        if (!visited[i]) {
            DFS(i + 1, visited);
            res++;
        }
    

    delete[] visited;
    printf("%d\n", res);
}

void Graphs::bipartiteness() {
    int* color = new int[currentSize];
    Stack stack;

    for (int i = 0; i < currentSize; i++) 
        color[i] = NONE;
    

    for (int i = 0; i < currentSize; i++) {
        if (color[i] == NONE) {
            stack.push(i+1);
            color[i] = A;

            while (!stack.isEmpty()) {
                int top = stack.pop();

                for (int j = 0; j < mainList[top - 1].getSize(); j++) {
                    int neighbour = mainList[top - 1][j];

                    if(color[neighbour - 1] == NONE){
                        color[neighbour - 1] = -color[top - 1];
                        stack.push(neighbour);
                    }
                    else {
                        if (color[neighbour - 1] == color[top - 1]) {
                            printf("F\n");
                            delete[] color;
                            return;
                        }
                    }
                }
            }
        }
    }

    delete[] color;

    printf("T\n");
}

void Graphs::verticesColoring(bool flag = false) {
    int* color = new int[currentSize];
    bool* usedColors = new bool[currentSize];
    int* order = new int[currentSize];


    for (int i = 0; i < currentSize; i++) {
        color[i] = NONE;
        usedColors[i] = false;
        order[i] = i;
    }

    if (flag) mergeSort(order, 0, currentSize - 1, true);
    

    for (int k = 0; k < currentSize; k++) {
        int i = order[k];
        color[i] = 0;

        for (int j = 0; j < mainList[i].getSize(); j++) {
            int adjacent = mainList[i][j] - 1;

            if (color[adjacent] != NONE) 
                usedColors[color[adjacent]] = true;
            
        }

        int clr = 0;
        for (clr; clr < currentSize; clr++) {
            if (!usedColors[clr]) {
                break;
            }
        }

        color[i] = clr;

        for (int j = 0; j < mainList[i].getSize(); j++) {
            int adjacent = mainList[i][j] - 1;

            if (color[adjacent] != NONE)
                usedColors[color[adjacent]] = false;

        }
    }


    for (int i = 0; i < currentSize; i++) 
        printf("%d ", color[i] + 1);
    printf("\n");

    delete[] color;
    delete[] usedColors;
    delete[] order;
}

void Graphs::mainLoop() {
    scanf("%d", &nrOfGraphs);

    while (nrOfGraphs--) {
        scanf("%d", &currentSize);

        mainList = new Vector[currentSize];

        for (int i = 0; i < currentSize; i++) {
            int temp;
            scanf("%d", &temp);

            mainList[i].reserve(temp);

            while (temp--) {
                int temp2 = 0;
                scanf("%d", &temp2);
                mainList[i].pushBack(temp2);
            }
        }
            
        degreeSequence();
        numberOfSequences();

        bipartiteness();
        printf("?\n");

        printf("?\n");
        verticesColoring();

        verticesColoring(true);
        printf("?\n");

        printf("?\n");
        complementsEdges();


        for (int i = 0; i < currentSize; i++) 
            mainList[i].clear();
        
        delete[] mainList;
    }
}
