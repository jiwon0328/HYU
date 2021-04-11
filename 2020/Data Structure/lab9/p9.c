#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ORDER 3
typedef struct B_node *BTree;
struct B_node {
    int n_keys;
    struct B_node *child[ORDER + 1];
    int key[ORDER];
    
    int isLeaf;
    int isRoot;
};

BTree initTree();
BTree insert(BTree bTree, int key);
BTree split(BTree bTree);
void inorder(BTree bTree, FILE* file);

int main() {
    FILE * inputFile = fopen("input.txt", "r");
    FILE * outputFile = fopen("output.txt", "w");
    
    if(inputFile == NULL) {
        fprintf(outputFile, "FILE OPEN ERROR!\n");
        return 0;
    }
    
    char tmp[100];
    int num;
    
    
    BTree bTree;
    bTree = initTree();
    bTree->isRoot = 1;
    
    while(fscanf(inputFile, "%s", tmp) != EOF) {
        if(strcmp(tmp, "i") == 0) {
            fscanf(inputFile, "%d", &num);
            bTree = insert(bTree, num);
        } else if(strcmp(tmp, "p") == 0) {
            inorder(bTree, outputFile);
            fprintf(outputFile, "\n");
        } else
            fprintf(outputFile, "COMMAND ERROR!\n");
    }
    
    return 0;
}

BTree initTree()
{
    int i;
    BTree newBTNode;
    newBTNode = (BTree)malloc(sizeof(struct B_node));
    newBTNode->n_keys = 0;
    newBTNode->isLeaf = 1;      
    newBTNode->isRoot = 0;
    for (i = 0; i < ORDER + 1; i++)
        newBTNode->child[i] = NULL;
    return newBTNode;
}

BTree insert(BTree bTree, int key) {
    int i, pos;
    BTree splitTree;
    if (bTree->isLeaf) {
        for (pos = 0; pos < bTree->n_keys; pos++) {
            if (bTree->key[pos] > key) break;
        }
        for (i = bTree->n_keys; i > pos; i--) {
            bTree->key[i] = bTree->key[i - 1];
        }
        bTree->key[pos] = key;
        bTree->n_keys += 1;
        if (bTree->n_keys == ORDER && bTree->isRoot) {
            return split(bTree);
        }
        return bTree;
    }
    
    else {
        for (pos = 0; pos < bTree->n_keys; pos++) {
            if (bTree->key[pos] > key) {
                break;
            }
        }
        bTree->child[pos] = insert(bTree->child[pos], key);
        if (bTree->child[pos]->n_keys == ORDER) {
            splitTree = split(bTree->child[pos]);
            for (i = bTree->n_keys; i > pos; i--) {
                bTree->key[i] = bTree->key[i - 1];
                bTree->child[i + 1] = bTree->child[i];
            }
            bTree->key[pos] = splitTree->key[0];
            bTree->n_keys += 1;
            bTree->child[pos] = splitTree->child[0];
            bTree->child[pos + 1] = splitTree->child[1];
        }
        if (bTree->n_keys == ORDER && bTree->isRoot) {
            return split(bTree);
        }
        return bTree;
    }
}

BTree split(BTree bTree) {
    int i, mid;
    BTree newParent;
    BTree newSibling;
    newParent = initTree();
    newParent->isLeaf = 0;
    if (bTree->isRoot) {
        newParent->isRoot = 1;
    }
    bTree->isRoot = 0;
    newSibling = initTree();
    newSibling->isLeaf = bTree->isLeaf;
    mid = (ORDER - 1) / 2;
    for (i = mid + 1; i < ORDER; i++) {
        newSibling->child[i - (mid + 1)] = bTree->child[i];
        newSibling->key[i - (mid + 1)] = bTree->key[i];
        newSibling->n_keys++;
        bTree->child[i] = NULL;
        bTree->key[i] = 0;
        bTree->n_keys--;
    }
    newSibling->child[i - (mid + 1)] = bTree->child[i];
    bTree->child[i] = NULL;
    newParent->key[0] = bTree->key[mid];
    newParent->n_keys++;
    bTree->key[mid] = 0;
    bTree->n_keys--;
    newParent->child[0] = bTree;
    newParent->child[1] = newSibling;
    return newParent;
}

void inorder(BTree bTree, FILE* file) {
    int i;
    for (i = 0; i < bTree->n_keys; i++) {

        if (!(bTree->isLeaf)) {
            inorder(bTree->child[i], file);
        }

        fprintf(file, "%d ", bTree->key[i]);
    }

    if (!(bTree->isLeaf)) {
        inorder(bTree->child[i], file);
    }
}
