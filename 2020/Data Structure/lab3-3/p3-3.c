#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EmptyTOS (-1)
typedef struct StackRecod *Stack;
typedef struct NumStackRecord *NumStack;

struct StackRecod{
    int capacity;
    int topOfStack;
    char *array;
};

struct NumStackRecord{
    int capacity;
    int topOfStack;
    int *array;
};

void push(char x, Stack stack, FILE* file);
void pop(Stack stack, FILE* file);
char top(Stack stack, FILE* file);
int isFull(Stack stack);
int isEmpty(Stack stack);

int checkPrecedence(char operator);

void pushNum(int x, NumStack nStack, FILE* file);
int popNum(NumStack nStack, FILE* file);
int isNFull(NumStack nStack);
int isNEmpty(NumStack nStack);

int main(void) {
    FILE * inputFile = fopen("input3-3.txt", "r");
    FILE * outputFile = fopen("output3-3.txt", "w");
    
    if(inputFile == NULL) {
        fprintf(outputFile, "FILE OPEN ERROR!\n");
        return 0;
    }
  
    Stack newStack;
    newStack = malloc(sizeof(struct StackRecod));
    if(newStack == NULL)
        fprintf(outputFile, "Out of space!!\n");
    newStack->array = malloc(sizeof(char)* 100);
    if(newStack->array == NULL)
        fprintf(outputFile, "Out of space!!\n");
    newStack->capacity = 100;
    newStack->topOfStack = EmptyTOS;
    
    NumStack numStack;
    numStack = malloc(sizeof(struct NumStackRecord));
    if(numStack == NULL)
        fprintf(outputFile, "Out of space!!\n");
    numStack->array = malloc(sizeof(int)* 100);
    if(numStack->array == NULL)
        fprintf(outputFile, "Out of space!!\n");
    numStack->capacity = 100;
    numStack->topOfStack = EmptyTOS;
    
    
    char tmp;
    
    fprintf(outputFile, "Infix Form : ");
    while(1) {
        tmp = fgetc(inputFile);
        if(tmp == '#') {
            break;
        }
        else
            fprintf(outputFile, "%c", tmp);
    }
    
    fprintf(outputFile, "\n");
    fprintf(outputFile, "Postfix Form : ");
    
    rewind(inputFile);
    
    while(1) {
        tmp = fgetc(inputFile);
        
        if(tmp >= 48 && tmp <= 57) {
            fprintf(outputFile, "%c", tmp);
            pushNum((tmp-48), numStack, outputFile);
        } else if(tmp == ')') {
            int n1, n2;
            while(1) {
                if(top(newStack, outputFile) == '+') {
                    n1 = popNum(numStack, outputFile);
                    n2 = popNum(numStack, outputFile);
                    pushNum((n2+n1), numStack, outputFile);
                } else if(top(newStack, outputFile) == '-') {
                    n1 = popNum(numStack, outputFile);
                    n2 = popNum(numStack, outputFile);
                    pushNum((n2-n1), numStack, outputFile);
                } else if(top(newStack, outputFile) == '*') {
                    n1 = popNum(numStack, outputFile);
                    n2 = popNum(numStack, outputFile);
                    pushNum((n2*n1), numStack, outputFile);
                } else if(top(newStack, outputFile) == '%') {
                    n1 = popNum(numStack, outputFile);
                    n2 = popNum(numStack, outputFile);
                    pushNum((n2%n1), numStack, outputFile);
                } else if(top(newStack, outputFile) == '/') {
                    n1 = popNum(numStack, outputFile);
                    n2 = popNum(numStack, outputFile);
                    pushNum((n2/n1), numStack, outputFile);
                } else
                    continue;
                
                fprintf(outputFile, "%c", top(newStack, outputFile));
                pop(newStack, outputFile);
                if(top(newStack, outputFile) == '(') {
                    pop(newStack, outputFile);
                    break;
                }
            }
        } else if(tmp == '(') {
            push(tmp, newStack, outputFile);
        } else if(tmp == '#') {
            int n1, n2;
            while(1) {
                if(top(newStack, outputFile) == '+') {
                    n1 = popNum(numStack, outputFile);
                    n2 = popNum(numStack, outputFile);
                    pushNum((n2+n1), numStack, outputFile);
                } else if(top(newStack, outputFile) == '-') {
                    n1 = popNum(numStack, outputFile);
                    n2 = popNum(numStack, outputFile);
                    pushNum((n2-n1), numStack, outputFile);
                } else if(top(newStack, outputFile) == '*') {
                    n1 = popNum(numStack, outputFile);
                    n2 = popNum(numStack, outputFile);
                    pushNum((n2*n1), numStack, outputFile);
                } else if(top(newStack, outputFile) == '%') {
                    n1 = popNum(numStack, outputFile);
                    n2 = popNum(numStack, outputFile);
                    pushNum((n2%n1), numStack, outputFile);
                } else if(top(newStack, outputFile) == '/') {
                    n1 = popNum(numStack, outputFile);
                    n2 = popNum(numStack, outputFile);
                    pushNum((n2/n1), numStack, outputFile);
                } else
                    continue;
                
                fprintf(outputFile, "%c", top(newStack, outputFile));
                pop(newStack, outputFile);
                if(isEmpty(newStack) == 1)
                    break;
            } break;
        } else if(checkPrecedence(top(newStack, outputFile)) >= checkPrecedence(tmp)) {
            int n1, n2;
            while(1) {
                if(top(newStack, outputFile) == '+') {
                    n1 = popNum(numStack, outputFile);
                    n2 = popNum(numStack, outputFile);
                    pushNum((n2+n1), numStack, outputFile);
                } else if(top(newStack, outputFile) == '-') {
                    n1 = popNum(numStack, outputFile);
                    n2 = popNum(numStack, outputFile);
                    pushNum((n2-n1), numStack, outputFile);
                } else if(top(newStack, outputFile) == '*') {
                    n1 = popNum(numStack, outputFile);
                    n2 = popNum(numStack, outputFile);
                    pushNum((n2*n1), numStack, outputFile);
                } else if(top(newStack, outputFile) == '%') {
                    n1 = popNum(numStack, outputFile);
                    n2 = popNum(numStack, outputFile);
                    pushNum((n2%n1), numStack, outputFile);
                } else if(top(newStack, outputFile) == '/') {
                    n1 = popNum(numStack, outputFile);
                    n2 = popNum(numStack, outputFile);
                    pushNum((n2/n1), numStack, outputFile);
                } else
                    continue;
                
                fprintf(outputFile, "%c", top(newStack, outputFile));
                pop(newStack, outputFile);
                if(checkPrecedence(top(newStack, outputFile)) <= checkPrecedence(tmp)) {
                    push(tmp, newStack, outputFile);
                    break;
                }
            }
        } else
            push(tmp, newStack, outputFile);
    }
    int result;
    result = popNum(numStack, outputFile);

    fprintf(outputFile, "\n");
    fprintf(outputFile, "Evaluation Result : %d", result);
    
    fclose(inputFile);
    fclose(outputFile);
    free(newStack);
    free(newStack->array);
    free(numStack);
    free(numStack->array);
    return 0;
}

void push(char x, Stack stack, FILE* file) {
    if(isFull(stack))
        fprintf(file, "Full\n");
    else {
        stack->array[++stack->topOfStack] = x;
    }
}

void pop(Stack stack, FILE* file) {
    if(isEmpty(stack))
        fprintf(file, "Empty\n");
    else {
        stack->topOfStack--;
    }
}

char top(Stack stack, FILE* file) {
    if(!isEmpty(stack))
       return stack->array[stack->topOfStack];
    else {
        return 0;
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

int checkPrecedence(char operator) {
    if(operator == '*' || operator == '/' || operator == '%')
        return 2;
    else if(operator == '+' || operator == '-')
        return 1;
    else
        return 0;
}

void pushNum(int x, NumStack nStack, FILE* file) {
    if(isNFull(nStack))
        fprintf(file, "Full\n");
    else {
        nStack->array[++nStack->topOfStack] = x;
    }
}

int popNum(NumStack nStack, FILE* file) {
    int r;
    if(isNEmpty(nStack)) {
        fprintf(file, "Empty\n");
        r = 0;
    }
    else {
        r = nStack->array[nStack->topOfStack];
        nStack->topOfStack--;
    }
    return r;
}

int isNFull(NumStack nStack) {
    if(sizeof(nStack) >= nStack->capacity)
        return 1;
    else
        return 0;
}

int isNEmpty(NumStack nStack) {
    if(nStack->topOfStack == -1)
        return 1;
    else
        return 0;
}
