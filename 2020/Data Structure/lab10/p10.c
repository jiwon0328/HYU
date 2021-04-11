#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Graph* Graph;
struct _Graph {
    int size;
    int *node;
    int **matrix;
};

typedef struct _Queue* Queue;
struct _Queue{
    int *key;
    int first;
    int rear;
    int qsize;
    int max_queue_size;
};

Graph createGraph(int nodes[], FILE* file);
void insertEdge(Graph g, int a, int b);
void topSort(Graph g, FILE* file);
Queue makeNewQueue(int x, FILE* file);
void enqueue(Queue q, int x, FILE* file);
int dequeue(Queue q, FILE* file);
static int succ(int value, Queue queue);
int isFull(Queue q);
int isEmpty(Queue q);

int main(void) {
    FILE * inputFile = fopen("input.txt", "r");
    FILE * outputFile = fopen("output.txt", "w");
    
    if(inputFile == NULL) {
        fprintf(outputFile, "FILE OPEN ERROR!\n");
        return 0;
    }
    
    int *nodes = (int*) malloc(sizeof(int) * 10);
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

    Graph graph;
    graph = createGraph(nodes, outputFile);
    graph->size = size;
    
    char edge[100];
    char* ptr;
    int a;
    int b;
    
    while(fscanf(inputFile, "%s", edge) != EOF) {
        ptr = strtok(edge, "-");
        a = atoi(ptr);
        ptr = strtok(NULL, "-");
        b = atoi(ptr);
        
        insertEdge(graph, a, b);
    }
    
    // print matrix
    fprintf(outputFile, "Adjacency matrix\n");
    fprintf(outputFile, "  ");
    for(int i = 0; i < graph->size; i++) {
        fprintf(outputFile, "%d ", graph->node[i]);
    }
    
    fprintf(outputFile, "\n");
    
    for(int i = 0; i < graph->size; i++) {
        fprintf(outputFile, "%d ", graph->node[i]);
        for(int j = 0; j < graph->size; j++) {
            fprintf(outputFile, "%d ", graph->matrix[i][j]);
        }
        fprintf(outputFile, "\n");
    }
    
    fprintf(outputFile, "\n\n\n");
    
    // print top sort result
    fprintf(outputFile, "TopSort Result : ");
    topSort(graph, outputFile);
    
    free(graph->matrix);
    free(graph);
    
    return 0;
}

Graph createGraph(int nodes[], FILE* file) {
    Graph newGraph;
    newGraph = (Graph) malloc(sizeof(struct _Graph));
    if(newGraph == NULL)
        fprintf(file, "Out of space!!\n");
    
    newGraph->node = (int*) malloc(sizeof(int) * 10);
    if(newGraph->node == NULL)
        fprintf(file, "Out of space!!\n");
    newGraph->node = nodes;
    
    newGraph->size = 0;
    
    newGraph->matrix = (int**) malloc(sizeof(int*) * 10);
    for(int i = 0; i < 10; i++)
        newGraph->matrix[i] = (int*) malloc(sizeof(int) * 10);
    
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++)
            newGraph->matrix[i][j] = 0;
    }
    
    return newGraph;
}

void insertEdge(Graph g, int a, int b) {
    int aPos = 0, bPos = 0;
    
    for(int i = 0; i < g->size; i++) {
        if(g->node[i] == a)
            aPos = i;
        else if(g->node[i] == b)
            bPos = i;
    }
    
    g->matrix[aPos][bPos] = 1;
}

void topSort(Graph g, FILE* file) {
    int max = g->size;
    
    Queue queue = makeNewQueue(max + 1, file);
    int v, index = 0;
    int *inDeg = (int*) malloc(sizeof(int) * max);
    for(int i = 0; i < max; i++)
        inDeg[i] = 0;
    
    for(int i = 0; i < max; i++) {
        for(int j = 0; j < max; j++) {
            if(g->matrix[i][j] == 1)
                inDeg[j] += 1;
        }
    }

    for(int i = 0; i < max; i++) {
        if(inDeg[i] == 0) {
            enqueue(queue, g->node[i], file);
        }
    }
    
    while(!isEmpty(queue)) {
        v = dequeue(queue, file);
        fprintf(file, "%d ", v);
        
        for(int i = 0; i < max; i++) {
            if(g->node[i] == v) {
                index = i;
                break;
            }
        }
        
        for(int i = 0; i < max; i++) {
            if(g->matrix[index][i] == 1) {
                if(--inDeg[i] == 0)
                    enqueue(queue, g->node[i], file);
            }
        }
    }
    free(queue);
}

Queue makeNewQueue(int x, FILE* file) {
    Queue newQueue;
    newQueue = (Queue) malloc(sizeof(struct _Queue));   //malloc
    if(newQueue == NULL)
        fprintf(file, "Out of space!!\n");
    newQueue->key = (int*) malloc(sizeof(int) * 100);      //malloc
    if(newQueue->key == NULL)
        fprintf(file, "Out of space!!\n");
    newQueue->max_queue_size = x;
    newQueue->qsize = 0;
    newQueue->first = 1;
    newQueue->rear = 0;
    
    return newQueue;
}

void enqueue(Queue q, int x, FILE* file) {
    if(isFull(q))
        fprintf(file, "Full\n");
    else {
        q->qsize++;
        q->rear = succ(q->rear, q);
        q->key[q->rear] = x;
    }
}

int dequeue(Queue q, FILE* file) {
    int tmp;
    if(isEmpty(q)) {
        tmp = -1;
        fprintf(file, "Empty\n");
    } else {
        tmp = q->key[q->first];
        q->first++;
    }
    return tmp;
}

static int succ(int value, Queue q) {
    if(++value == q->max_queue_size)
        value = 0;
    return value;
}

int isFull(Queue q) {
    if(q->rear == q->max_queue_size - 1)
        return 1;
    else
        return 0;
}

int isEmpty(Queue q) {
    if(q->first > q->rear)
        return 1;
    else
        return 0;
}
