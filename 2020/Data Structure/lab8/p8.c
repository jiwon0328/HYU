#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct{
    int capacity;
    int size;
    int *elements;
};

void insert(int x, PriorityQueue h, FILE* file);
int find(int x, PriorityQueue h, FILE* file);
void print(PriorityQueue h, FILE* file);
int isFull(PriorityQueue h);
int findElement(int x, PriorityQueue h);

int main(void) {
    FILE * inputFile = fopen("input.txt", "r");
    FILE * outputFile = fopen("output.txt", "w");
    
    if(inputFile == NULL) {
        fprintf(outputFile, "FILE OPEN ERROR!\n");
        return 0;
    }
    
    char tmp[100];
    int num;
    int capacity;
    
    fscanf(inputFile, "%d", &capacity);
    
    PriorityQueue h = malloc(sizeof(struct HeapStruct));
    if(h == NULL) {
        fprintf(outputFile, "Out of space!!\n");
    } else {
        h->capacity = capacity;
        h->size = 0;
        h->elements = malloc(sizeof(int) * capacity);
    }
    
    while(fscanf(inputFile, "%s", tmp) != EOF) {
        if(strcmp(tmp, "i") == 0) {
            fscanf(inputFile, "%d", &num);
            insert(num, h, outputFile);
        } else if(strcmp(tmp, "f") == 0) {
            fscanf(inputFile, "%d", &num);
            find(num, h, outputFile);
        } else if(strcmp(tmp, "p") == 0) {
            print(h, outputFile);
            fprintf(outputFile, "\n");
        } else
            fprintf(outputFile, "COMMAND ERROR!\n");
    }
    return 0;
}

void insert(int x, PriorityQueue h, FILE* file) {
    if(h->size >= h->capacity) {
        fprintf(file, "heap is full\n");
        return;
    }
 
    if(findElement(x, h) > 0) {
        fprintf(file, "%d is already in the heap.\n", x);
        return;
    }
    
    int i;
    
    for(i = ++h->size; h->elements[i/2] < x; i/=2) {
        if(i == 1) {
            h->elements[i] = x;
            fprintf(file, "insert %d\n", x);
            return;
        }
        h->elements[i] = h->elements[i/2];
    }
    
    h->elements[i] = x;
    fprintf(file, "insert %d\n", x);
}

int find(int x, PriorityQueue h, FILE* file) {
    for(int i = 0; i < h->capacity; i++) {
        if(h->elements[i] == x) {
            fprintf(file, "%d is in the heap.\n", x);
            return x;
        }
    }
    fprintf(file, "%d is not in the heap.\n", x);
    return -1;
}

int findElement(int x, PriorityQueue h) {
    for(int i = 1; i <= h->size; i++) {
        if(h->elements[i] == x) {
            return x;
        }
    }
    return -1;
}

void print(PriorityQueue h, FILE* file) {
    for(int i = 1; i <= h->size; i++) {
        fprintf(file, "%d ", h->elements[i]);
    }
}
