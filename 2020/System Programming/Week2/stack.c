//Template
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int nData;
	struct Node *next;
}Node;

typedef struct Stack{
	Node *top;
}Stack;

void InitializeStack(Stack *stack);
void Push(Stack *stack, int nData);
int Pop(Stack *stack);


int main(void){
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    if(stack == NULL)
        printf("Out of space!!!\n");
    
    InitializeStack(stack);
    
    Push(stack, 1);
    Push(stack, 3);
    Push(stack, 5);
    Push(stack, 7);
    Push(stack, 9);
    
    printf("\n");
    
    int num;
    for(int i = 0; i < 3; i++) {
        num = Pop(stack);
        printf("Pop %d\n", num);
    }
    
	return 0;
}

void InitializeStack(Stack *stack){
    stack->top = NULL;
    printf("Initialize Stack\n\n");
}

void Push(Stack *stack, int nData){
    Node *newNode = (Node*) malloc(sizeof(Node));
    if(newNode == NULL)
        printf("Out of space!!!\n");
    
    newNode->nData = nData;
    
    newNode->next = stack->top;
    stack->top = newNode;
    
    printf("Push %d\n", nData);
}

int Pop(Stack *stack){
    Node *tmp;
    int popNum;
    
    // 빈 Stack인지 파악
    if(stack->top == NULL)
        printf("Stack is empty!!!\n");
    
    popNum = stack->top->nData;
    tmp = stack->top;
    
    stack->top = stack->top->next;
    
    free(tmp);
    
    return popNum;
}
