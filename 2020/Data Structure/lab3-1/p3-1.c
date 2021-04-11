#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EmptyTOS (-1)
typedef struct StackRecod *Stack;

struct StackRecod{
    int capacity;
    int topOfStack;
    int *array;
};

void push(int x, Stack stack, FILE* file);
void pop(Stack stack, FILE* file);
int isFull(Stack stack);
int isEmpty(Stack stack);

int main(void) {
    FILE * inputFile = fopen("input3-1.txt", "r");
    FILE * outputFile = fopen("output3-1.txt", "w");
    
    if(inputFile == NULL) {
        fprintf(outputFile, "FILE OPEN ERROR!\n");
        return 0;
    }
    
    Stack newStack;
    newStack = malloc(sizeof(struct StackRecod));   
    if(newStack == NULL)
        fprintf(outputFile, "Out of space!!\n");
    newStack->array = malloc(sizeof(int)*100);    
    if(newStack->array == NULL)
        fprintf(outputFile, "Out of space!!\n");
    newStack->capacity = 100;
    newStack->topOfStack = EmptyTOS;
    
    int num = 0;
    fscanf(inputFile, "%d", &num);
    char tmp[100];
    
    for(int i = 0; i < num; i++) {
        int tmpNum;
        fscanf(inputFile, "%s", tmp);
        
        if(strcmp(tmp, "push") == 0) {
            fscanf(inputFile, "%d", &tmpNum);
            push(tmpNum, newStack, outputFile);
        } else if(strcmp(tmp, "pop") == 0) {
            fscanf(inputFile, "%d", &tmpNum);
            pop(newStack, outputFile);
        } else
            fprintf(outputFile, "COMMAND ERROR\n");
    }
    fclose(inputFile);
    fclose(outputFile);
    free(newStack);
    free(newStack->array);
    return 0;
}

void push(int x, Stack stack, FILE* file) {
    if(isFull(stack))
        fprintf(file, "Full\n");
    else
        stack->array[++stack->topOfStack] = x;
}

void pop(Stack stack, FILE* file) {
    if(isEmpty(stack))
        fprintf(file, "Empty\n");
    else {
        fprintf(file, "%d\n", stack->array[stack->topOfStack]);
        stack->topOfStack--;
    }
}

int isFull(Stack stack) {
    if(sizeof(stack) >= stack->capacity)
        return 1;
    else
        return 0;
}

int isEmpty(Stack stack) {
    if(stack->topOfStack == -1)
        return 1;
    else
        return 0;
}
