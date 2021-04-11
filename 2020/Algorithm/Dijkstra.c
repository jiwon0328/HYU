#include <stdio.h>
#include <stdlib.h>

typedef struct edge Edge;
struct edge {
    int weight;
    int x, y;
};

typedef struct v {
    int distance;
    int name;
} Vertex;

typedef struct Heapstruct Heap;
struct Heapstruct {
    int size;
    Vertex* arr;
};

Heap* createHeap(int);
void heapify(Heap*, int);
int deleteMax(Heap*);
void insert(Heap*, int);

void relax(int* d, int u, int v, int **adjm, int *pi);
void dijkstra(int **adjm, int s, int n);

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    
    Edge *edges = (Edge*) malloc(sizeof(Edge) * m);
    for(int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].weight);
    }
    
    int** adjm = (int**) malloc(sizeof(int*) * (n + 1));
    for(int i = 0; i < n + 1; i++) {
        adjm[i] = (int*) malloc(sizeof(int) * (n + 1));
    }
    
    for(int i = 0; i < m; i++) {
        adjm[edges[i].x][edges[i].y] = edges[i].weight;
    }
    
    int* distances = (int*) malloc(sizeof(int) * (n + 1));
    int* pi = (int*) malloc(sizeof(int) * (n + 1));
    
    
    
    free(edges);
    
    return 0;
}

void relax(int *d, int u, int v, int **adjm, int *pi) {
    if(d[v] > d[u] + adjm[u][v]) {
        d[v] = d[u] + adjm[u][v];
        pi[v] = u;
    }
}

void dijkstra(int **adjm, int s, int n) {
    Heap* heap = createHeap(n);
    insert(heap, s);
    heap->arr[0].distance = 0;
    for(int i = 1; i < n + 1; i++) {
        
    }
    
    
}

Heap* createHeap(int size) {
    Heap* tmp;
    tmp = (Heap*) malloc(sizeof(Heap));
    tmp->size = 0;
    tmp->arr = (Vertex*) malloc(sizeof(Vertex) * (size + 1));

    return tmp;
}

void heapify(Heap* Uheap, int n) {
    int child = n * 2;
    int tmp;
    if (Uheap->size >= child) {
        if (child != Uheap->size && Uheap->arr[child].name <= Uheap->arr[child + 1].name) child++;
        if (Uheap->arr[child].name > Uheap->arr[n].name) {
            tmp = Uheap->arr[n].name;
            Uheap->arr[n] = Uheap->arr[child];
            Uheap->arr[child].name = tmp;
            heapify(Uheap, child);
        }
    }

}

void insert(Heap* heap, int value) {
    int i;
    
    for (i = ++heap->size; i / 2 > 0 && heap->arr[i / 2].name < value; i /= 2) {
        heap->arr[i] = heap->arr[i / 2];
    }
    
    heap->arr[i].name = value;
    heap->arr[i].distance = 999;
}

int deleteMax(Heap* heap) {
    int i, child, max, end;
    max = heap->arr[1].name;
    end = heap->arr[heap->size--].name;

    for (i = 1; i * 2 <= heap->size; i = child) {
        child = i * 2;
        
        if (child != heap->size && heap->arr[child].name <= heap->arr[child + 1].name)
            child++;
        if (end < heap->arr[child].name)
            heap->arr[i] = heap->arr[child];
        else
            break;
    }
    
    heap->arr[i].name = end;
    
    return max;
}
