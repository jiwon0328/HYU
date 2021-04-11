#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;

struct AVLNode {
    int element;
    AVLTree left;
    AVLTree right;
    int height;
};

int height(Position position);
AVLTree insert(int x, AVLTree tree, FILE* file);
Position singleRotateWithLeft(Position unbalanced);
Position singleRotateWithRight(Position unbalanced);
Position doubleRotateWithLeft(Position unbalanced);
Position doubleRotateWithRight(Position unbalanced);
int max(int h1, int h2);
AVLTree find(int x, AVLTree tree);
void printTree(AVLTree root, FILE* file);
void freeTree(AVLTree tree);


int main(void) {
    FILE * inputFile = fopen("input.txt", "r");
    FILE * outputFile = fopen("output.txt", "w");
    
    if(inputFile == NULL) {
        fprintf(outputFile, "FILE OPEN ERROR!\n");
        return 0;
    }
    
    AVLTree tree = NULL;
    int value;
    
    while(fscanf(inputFile, "%d", &value) != EOF) {
        if(find(value, tree) == NULL) {
            tree = insert(value, tree, outputFile);
            printTree(tree, outputFile);
            fprintf(outputFile, "\n");
        } else {
            fprintf(outputFile, "%d already in the tree!\n", value);
        }
    }
    
    freeTree(tree);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

int height(Position position) {
    if(position == NULL)
        return -1;
    else
        return position->height;
}

AVLTree insert(int x, AVLTree tree, FILE* file) {
    if(tree == NULL) {
        tree = malloc(sizeof(struct AVLNode));
        if(tree == NULL)
            fprintf(file, "Out of space!!");
        else {
            tree->element = x;
            tree->height = 0;
            tree->left = tree->right = NULL;
        }
    } else if(x < tree->element) {
        tree->left = insert(x, tree->left, file);
        if(height(tree->left) - height(tree->right) == 2) {
            if(x < tree->left->element)
                tree = singleRotateWithLeft(tree);
            else
                tree = doubleRotateWithLeft(tree);
        }
    } else if(x > tree->element) {
        tree->right = insert(x, tree->right, file);
        if(height(tree->right) - height(tree->left) == 2) {
            if(x > tree-> right->element)
                tree = singleRotateWithRight(tree);
            else
                tree = doubleRotateWithRight(tree);
        }
    }
    
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    return tree;
}

Position singleRotateWithLeft(Position unbalnced) {
    Position new;
    new = unbalnced->left;
    unbalnced->left = new->right;
    new->right = unbalnced;
    
    unbalnced->height = max(height(unbalnced->left), height(unbalnced->right)) + 1;
    new->height = max(height(new->left), height(new->right)) + 1;
    
    return new;
}

Position singleRotateWithRight(Position unbalnced) {
    Position new;
    new = unbalnced->right;
    unbalnced->right = new->left;
    new->left = unbalnced;
    
    unbalnced->height = max(height(unbalnced->left), height(unbalnced->right)) + 1;
    new->height = max(height(new->left), height(new->right)) + 1;
    
    return new;
}

Position doubleRotateWithLeft(Position unbalnced) {
    unbalnced->left = singleRotateWithRight(unbalnced->left);
    return singleRotateWithLeft(unbalnced);
}

Position doubleRotateWithRight(Position unbalnced) {
    unbalnced->right = singleRotateWithLeft(unbalnced->right);
    return singleRotateWithRight(unbalnced);
}

int max(int h1, int h2) {
    if(h1 >= h2)
        return h1;
    else
        return h2;
}

AVLTree find(int x, AVLTree tree) {
    if(tree == NULL)
        return NULL;
    if(x < tree->element)
        return find(x, tree->left);
    else if(x > tree->element)
        return find(x, tree->right);
    else
        return tree;
}

void printTree(AVLTree tree, FILE* file) {
    if(tree) {
        printTree(tree->left, file);
        fprintf(file, "%d(%d) ", tree->element, tree->height);
        printTree(tree->right, file);
    }
}

void freeTree(AVLTree tree) {
    if(tree) {
        freeTree(tree->left);
        freeTree(tree->right);
        free(tree);
    }
}
