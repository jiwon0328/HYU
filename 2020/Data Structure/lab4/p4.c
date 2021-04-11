#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ThreadedTree *ThreadedPtr;
struct ThreadedTree {
    short int leftThread;
    ThreadedPtr leftChild;
    char data;
    ThreadedPtr rightChild;
    short int rightThread;
};

ThreadedPtr insucc(ThreadedPtr tree);
void tinorder(ThreadedPtr tree, FILE* file);
void insertLeftNode(ThreadedPtr new, ThreadedPtr parent);
void insertRightNode(ThreadedPtr new, ThreadedPtr parent);

int main(void) {
    FILE * inputFile = fopen("input.txt", "r");
    FILE * outputFile = fopen("output.txt", "w");
    
    if(inputFile == NULL) {
        fprintf(outputFile, "FILE OPEN ERROR!\n");
        return 0;
    }
    
    int num = 0;
    fscanf(inputFile, "%d", &num);
    
    fgetc(inputFile);
    
    ThreadedPtr root;
    root = (ThreadedPtr)malloc(sizeof(struct ThreadedTree));
    if(root == NULL)
        fprintf(outputFile, "Out of space!!");
    else {
        root->data = 'R';
        root->leftThread = 1;
        root->leftChild = root;
        root->rightChild = root;
        root->rightThread = 0;
    }
    
    ThreadedPtr* arr;
    arr = (ThreadedPtr*)malloc(sizeof(ThreadedPtr) * (num + 1));
    if(arr == NULL) {
        fprintf(outputFile, "Out of space!!");
    } else {
        arr[0] = root;
    }
    
    char x;
    
    for(int i = 1; i < (num + 1); i++) {
        ThreadedPtr newTree;
        newTree = (ThreadedPtr)malloc(sizeof(struct ThreadedTree));
        if(newTree == NULL) {
            fprintf(outputFile, "Out of space!!");
        } else {
            newTree->leftThread = 1;
            newTree->leftChild = root;
            newTree->rightChild = root;
            newTree->rightThread = 1;
        }
        
        x = fgetc(inputFile);
        
        newTree->data = x;
        
        int parent;
        parent = i/2;
        
        arr[i] = newTree;
        
        if(i == 1) {
            insertLeftNode(newTree, root);
        } else if(i % 2 == 0) {
            insertLeftNode(newTree, arr[parent]);
        } else {
            insertRightNode(newTree, arr[parent]);
        }
        fgetc(inputFile);
    }
    
    tinorder(root, outputFile);
    
    for(int i = 0; i < (num+1); i++) {
        free(arr[i]);
    }
    
    free(arr);
    
    fclose(inputFile);
    fclose(outputFile);
    
    
    return 0;
}


ThreadedPtr insucc(ThreadedPtr tree) {
    ThreadedPtr temp;
    temp = tree->rightChild;
    if(!tree->rightThread)
        while(!temp->leftThread) {
            temp = temp->leftChild;
        }
    return temp;
}

void tinorder(ThreadedPtr tree, FILE* file) {
    ThreadedPtr temp = tree;
    for(;;) {
        temp = insucc(temp);
        if(temp == tree)
            break;
        fprintf(file, "%-3c", temp->data);
    }
}

void insertLeftNode(ThreadedPtr new, ThreadedPtr parent) {
    new->leftChild = parent->leftChild;
    parent->leftChild = new;
    parent->leftThread = 0;
    new->rightChild = parent;
}

void insertRightNode(ThreadedPtr new, ThreadedPtr parent) {
    new->rightChild = parent->rightChild;
    parent->rightChild = new;
    parent->rightThread = 0;
    new->leftChild = parent; 
}
