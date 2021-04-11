#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct _Node* Node;
struct _Node {
    int key;
    int weight;
};

typedef struct _Heap* Heap;
struct _Heap {
    int capacity;
    int size;
    Node element;
};

typedef struct _Graph* Graph;
struct _Graph {
    int size;
    int *node;
    int **matrix;
};

Graph createGraph(int nodes[], FILE* file);
void insertEdge(Graph g, int a, int b, int weight);
Heap createMinHeap(int heapSize, FILE* file);
void insert(Heap minHeap, int vertex, int weight, FILE* file);
int deleteMin(Heap minHeap);
int* dijkstra(Graph g, int s, FILE* file);
int findIndex(Graph g, int k);
int findValue(Graph g, int index);
int isEmpty(Heap h);
void decreasePriority(Heap h, int v, int weight, FILE* file);
void update(Heap h, int v, int weight);
void printShortestPath(int pred[], int s, int e, FILE* file);

int main(void) {
    FILE * inputFile = fopen("input.txt", "r");
    FILE * outputFile = fopen("output.txt", "w");
    
    if(inputFile == NULL) {
        fprintf(outputFile, "FILE OPEN ERROR!\n");
        return 0;
    }
    
    int *nodes = (int*) malloc(sizeof(int) * 100);
    int tmp;
    int size = 0;
    
    while(1) {
        tmp = fgetc(inputFile) - 48;
        nodes[size] = tmp;
        size++;
        if(fgetc(inputFile) == 10) {
            break;
        }
    }
    
    Graph graph = createGraph(nodes, outputFile);
    graph->size = size;
    
    char edge[100];
    char* ptr;
    int a;
    int b;
    int weight;
    
    while(1) {
        fscanf(inputFile, "%s", edge);
        
        if(strchr(edge, '-') == NULL)
            break;
        
        ptr = strtok(edge, "-");
        a = atoi(ptr);
        ptr = strtok(NULL, "-");
        b = atoi(ptr);
        ptr = strtok(NULL, "-");
        weight = atoi(ptr);
        
        insertEdge(graph, a, b, weight);
    }
    int start, end;
    start = atoi(edge);
    fscanf(inputFile, "%d", &end);
    
    int *pred = dijkstra(graph, start, outputFile);
    
    printShortestPath(pred, start, end, outputFile);
    
    return 0;
}

Graph createGraph(int nodes[], FILE* file) {
    Graph newGraph;
    newGraph = (Graph) malloc(sizeof(struct _Graph));
    if(newGraph == NULL)
        fprintf(file, "Out of space!!\n");
    
    newGraph->node = (int*) malloc(sizeof(int) * 100);
    if(newGraph->node == NULL)
        fprintf(file, "Out of space!!\n");
    newGraph->node = nodes;
    
    newGraph->size = 0;
    
    newGraph->matrix = (int**) malloc(sizeof(int*) * 100);
    for(int i = 0; i < 10; i++)
        newGraph->matrix[i] = (int*) malloc(sizeof(int) * 100);
    
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++)
            newGraph->matrix[i][j] = 0;
    }
    
    return newGraph;
}

void insertEdge(Graph g, int a, int b, int weight) {
    int aPos = 0, bPos = 0;
    
    for(int i = 0; i < g->size; i++) {
        if(g->node[i] == a)
            aPos = i;
        else if(g->node[i] == b)
            bPos = i;
    }
    
    g->matrix[aPos][bPos] = weight;
}

Heap createMinHeap(int heapSize, FILE* file) {
    Heap newHeap = malloc(sizeof(struct _Heap));
    if(newHeap == NULL)
        fprintf(file, "Out of space!!\n");
    else {
        newHeap->capacity = 100;
        newHeap->size = 0;
        newHeap->element = malloc(sizeof(struct _Node) * 100);
    }
    
    return newHeap;
}

void insert(Heap minHeap, int vertex, int weight, FILE* file) {
    if(minHeap->size >= minHeap->capacity) {
        fprintf(file, "heap is full\n");
        return;
    }
    
    int i;
    for(i = ++minHeap->size; minHeap->element[i/2].weight > weight; i/=2)
        minHeap->element[i] = minHeap->element[i/2];
    
    minHeap->element[i].key = vertex;
    minHeap->element[i].weight = weight;
    
}

int deleteMin(Heap minHeap) {
    int i, child;
    int minElement, lastElement;
    int lastWeight;
    int size = minHeap->size--;
    
    minElement = minHeap->element[1].key;
    lastElement = minHeap->element[size].key;
    lastWeight = minHeap->element[size].weight;
    
    for(i = 1; i * 2 <= minHeap->size; i = child) {
        child = i * 2;
        if(child != minHeap->size && minHeap->element[child + 1].weight < minHeap->element[child].weight)
            child++;
        
        if(lastWeight > minHeap->element[child].weight)
            minHeap->element[i] = minHeap->element[child];
        else
            break;
    }
    
    minHeap->element[i].key = lastElement;
    minHeap->element[i].weight = lastWeight;
    
    return minElement;
}

int* dijkstra(Graph g, int s, FILE* file) {
    int d[100];
    int *pred = (int*) malloc(sizeof(int) * 100);
    
    for(int i = 0; i < g->size; i++) {
        int v = findValue(g, i);
        d[v] = 999;
        pred[v] = 0;
    }
    
    d[s] = 0;
    int sIndex = findIndex(g, s);
    
    for(int i = 0; i < g->size; i++) {
        int weight = g->matrix[sIndex][i];
        if(weight > 0) {
            int v = findValue(g, i);
            d[v] = weight;
            pred[v] = s;
        }
    }
    
    Heap minHeap = createMinHeap(100, file);
    for(int i = 0; i < g->size; i++) {
        int v = findValue(g, i);
        insert(minHeap, v, d[v], file);
    }
    
    while(isEmpty(minHeap) != 1) {
        int u = deleteMin(minHeap);
        int uIndex = findIndex(g, u);
        
        for(int i = 0; i < g->size + 1; i++) {
            int weight = g->matrix[uIndex][i];
            if(weight > 0) {
                int v = findValue(g, i);
                if(d[u] + weight < d[v]) {
                    d[v] = d[u] + weight;
                    pred[v] = u;
                    decreasePriority(minHeap, i, d[v], file);
                }
            }
        }
    }
    return pred;
}

int findIndex(Graph g, int k) {
    int i;
    for(i = 0; i < g->size; i++) {
        if(g->node[i] == k)
            break;
    }
    return i;
}

int findValue(Graph g, int index) {
    int value = g->node[index];
    return value;
}

int isEmpty(Heap h) {
    if(h->size > 0)
        return 0;
    
    return 1;
}

void decreasePriority(Heap h, int v, int weight, FILE* file) {
    for(int i = 0; i < h->size; i++) {
        if(h->element[i].key == v) {
            update(h, v, weight);
            return;
        }
    }
    
    insert(h, v, weight, file);
}

void update(Heap h, int index, int weight) {
    h->element[index].weight = weight;
    
    while(index > 0 && h->element[index].weight < h->element[(index - 1) / 2].weight) {
        Node tmp = &h->element[index];
        h->element[index] = h->element[(index - 1) / 2];
        h->element[(index - 1) / 2] = *tmp;
        
        index = (index - 1) / 2;
    }
}

void printShortestPath(int pred[], int s, int e, FILE* file) {
    int load[100];
    int i = 0;
    int node = e;
    while(1) {
        load[i] = node;
        i++;
        node = pred[node];
        if(node == s) {
            load[i] = node;
            break;
        }
        
        if(node == 0) {
            fprintf(file, "No Path\n");
            return;
        }
    }
    
    for(int j = i; j >= 0; j--) {
        fprintf(file, "%d ", load[j]);
    }
    fprintf(file, "\n");
}
