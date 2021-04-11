#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode *TreePtr;
struct TreeNode {
    int value;
    TreePtr left, right;
};

TreePtr insertNode(int value, TreePtr root, FILE* file);
TreePtr findMax(TreePtr root);
TreePtr deleteNode(int value, TreePtr root, FILE* file);
TreePtr findNode(int value, TreePtr root);
void printInorder(TreePtr root, FILE* file);
void printPreorder(TreePtr root, FILE* file);
void printPostorder(TreePtr root, FILE* file);

int main(void) {
    FILE * inputFile = fopen("input.txt", "r");
    FILE * outputFile = fopen("output.txt", "w");
    
    if(inputFile == NULL) {
        fprintf(outputFile, "FILE OPEN ERROR!\n");
        return 0;
    }
    
    TreePtr root = NULL;
    
    char tmp[100];
    int value;
    
    while(fscanf(inputFile, "%s", tmp) != EOF) {
        if(strcmp(tmp, "i") == 0) {
            fscanf(inputFile, "%d", &value);
            if(findNode(value, root) == NULL)
                root = insertNode(value, root, outputFile);
            else
                fprintf(outputFile,"%d already exists.\n", value);
        } else if(strcmp(tmp, "d") == 0) {
            fscanf(inputFile, "%d", &value);
            if(findNode(value, root) == NULL)
                fprintf(outputFile, "Deletion failed. %d does not exits.\n", value);
            else
                root = deleteNode(value, root, outputFile);
        } else if(strcmp(tmp, "f") == 0) {
            fscanf(inputFile, "%d", &value);
            if(findNode(value, root) == NULL)
                fprintf(outputFile, "%d is not in the tree.\n", value);
            else
                fprintf(outputFile, "%d is in the tree.\n", value);
        } else if(strcmp(tmp, "pi") == 0) {
            fprintf(outputFile, "pi -");
            printInorder(root, outputFile);
            fprintf(outputFile, "\n");
        } else if(strcmp(tmp, "pr") == 0) {
            fprintf(outputFile, "pr -");
            printPreorder(root, outputFile);
            fprintf(outputFile, "\n");
        } else if(strcmp(tmp, "po") == 0) {
            fprintf(outputFile, "po -");
            printPostorder(root, outputFile);
            fprintf(outputFile, "\n");
        } else
            fprintf(outputFile, "COMMAND ERROR!\n");
    }
    
    free(root);
    return 0;
}

TreePtr insertNode(int value, TreePtr root, FILE* file) {
    if(root == NULL) {
        root = malloc(sizeof(struct TreeNode));
        if(root == NULL)
            fprintf(file, "Out of space!!\n");
        else {
            root->value = value;
            root->left = root->right = NULL;
        }
    } else if(value < root->value) {
        root->left = insertNode(value, root->left, file);
    } else if(value > root->value) {
        root->right = insertNode(value, root->right, file);
    }
    return root;
}

TreePtr findMax(TreePtr root) {
    if(root == NULL)
        return NULL;
    else {
        while(root->right != NULL)
            root = root->right;
    }
    return root;
}

TreePtr deleteNode(int value, TreePtr root, FILE* file) {
    TreePtr tmpCell;
    if(root == NULL)
        fprintf(file, "Element not found\n");
    else if(value < root->value)
        root->left = deleteNode(value, root->left, file);
    else if(value > root->value)
        root->right = deleteNode(value, root->right, file);
    else if(root->left != NULL && root->right != NULL) {
        tmpCell = findMax(root->left);
        root->value = tmpCell->value;
        root->left = deleteNode(root->value, root->left, file);
    } else {
        tmpCell = root;
        if(root->left == NULL)
            root = root->right;
        else if(root->right == NULL)
            root = root->left;
        free(tmpCell);
    }
    return root;
}

TreePtr findNode(int value, TreePtr root) {
    if(root == NULL)
        return NULL;
    if(value < root->value)
        return findNode(value, root->left);
    else if(value > root->value)
        return findNode(value, root->right);
    else
        return root;
}
void printInorder(TreePtr root, FILE* file) {
    if(root) {
        printInorder(root->left, file);
        fprintf(file, "%2d", root->value);
        printInorder(root->right, file);
    }
}
void printPreorder(TreePtr root, FILE* file) {
    if(root) {
        fprintf(file, "%2d", root->value);
        printPreorder(root->left, file);
        printPreorder(root->right, file);
    }
}
void printPostorder(TreePtr root, FILE* file) {
    if(root) {
        printPostorder(root->left, file);
        printPostorder(root->right, file);
        fprintf(file, "%2d", root->value);
    }
}

