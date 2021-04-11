#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100

typedef struct QueueRecord *Queue;
struct QueueRecord {
    int capacity;
    int front;
    int rear;
    int size;
    int *array;
};

void enQueue (int x, Queue queue, FILE* file);
void deQueue (Queue queue, FILE* file);
int isFull(Queue queue);
int isEmpty(Queue queue);
static int succ(int value, Queue queue);

int main(void) {
    FILE * inputFile = fopen("input3-2.txt", "r");
    FILE * outputFile = fopen("output3-2.txt", "w");
    
    if(inputFile == NULL) {
        fprintf(outputFile, "FILE OPEN ERROR!\n");
        return 0;
    }
    
    Queue newQueue;
    newQueue = malloc(sizeof(struct QueueRecord));   
    if(newQueue == NULL)
        fprintf(outputFile, "Out of space!!\n");
    newQueue->array = malloc(sizeof(int)*100);      
    if(newQueue->array == NULL)
        fprintf(outputFile, "Out of space!!\n");
    newQueue->capacity = MAX_QUEUE_SIZE;
    newQueue->size = 0;
    newQueue->front = 1;
    newQueue->rear = 0;
    
    int num = 0;
    fscanf(inputFile, "%d", &num);
    char tmp[100];
    
    for(int i = 0; i < num; i++) {
        int tmpNum;
        fscanf(inputFile, "%s", tmp);
        if(strcmp(tmp, "enQ") == 0) {
            fscanf(inputFile, "%d", &tmpNum);
            enQueue(tmpNum, newQueue, outputFile);
        } else if(strcmp(tmp, "deQ") == 0) {
            fscanf(inputFile, "%d", &tmpNum);
            deQueue(newQueue, outputFile);
        } else
            fprintf(outputFile, "COMMAND ERROR\n");
    }
    fclose(inputFile);
    fclose(outputFile);
    free(newQueue);
    free(newQueue->array);
    return 0;
}

static int succ(int value, Queue queue) {
    if(++value == queue->capacity)
        value = 0;
    return value;
}

void enQueue (int x, Queue queue, FILE* file) {
    if(isFull(queue))
        fprintf(file, "Full\n");
    else {
        queue->size++;
        queue->rear = succ(queue->rear, queue);
        queue->array[queue->rear] = x;
    }
}

void deQueue (Queue queue, FILE* file) {
    if(isEmpty(queue))
        fprintf(file, "Empty\n");
    else {
        fprintf(file, "%d\n", queue->array[queue->front]);
        queue->front++;
    }
}

int isFull(Queue queue) {
    if(queue->rear == MAX_QUEUE_SIZE - 1)
        return 1;
    else
        return 0;
}

int isEmpty(Queue queue) {
    if(queue->front > queue->rear)
        return 1;
    else
        return 0;
}
