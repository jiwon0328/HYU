#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode* Position;
typedef Position List;
typedef struct HashTbl* HashTable;

struct ListNode {
    int element;
};

struct HashTbl {
    int tableSize;
    List* theList;
};

void insert(HashTable h, int value, int solution, FILE* file);
void delete(HashTable h, int value, int solution, FILE* file);
int find(HashTable h, int value, int solution);
void print(HashTable h, FILE* file);
int hash(int value, int size, int i, int solution);
int findForInsert(HashTable h, int value, int solution);
int findForDelete(HashTable h, int value, int solution);

int main(void) {
    FILE * inputFile = fopen("input.txt", "r");
    FILE * outputFile = fopen("output.txt", "w");
    
    if(inputFile == NULL) {
        fprintf(outputFile, "FILE OPEN ERROR!\n");
        return 0;
    }
    
    int tmp;
    int value, size, sol;
    char solution[100];
    char temp[100];
    
    
    fscanf(inputFile, "%d", &tmp);
    
    for(int i = 0; i < tmp; i++) {
        fscanf(inputFile, "%s", solution);
        if(strcmp(solution, "Linear") == 0) {
            sol = 1;
            fprintf(outputFile, "Linear\n");
        } else if(strcmp(solution, "Quadratic") == 0) {
            sol = 2;
            fprintf(outputFile, "Quadratic\n");
        } else if(strcmp(solution, "Double") == 0) {
            sol = 3;
            fprintf(outputFile, "Double\n");
        } else {
            fprintf(outputFile, "No Command.\n");
            return 0;
        }
        
        fscanf(inputFile, "%d", &size);
        
        HashTable hashTable = (HashTable) malloc(sizeof(struct HashTbl));
        hashTable->theList = (List*) malloc(sizeof(List) * size);
        hashTable->tableSize = size;
        
        for(int i = 0; i < size; i++) {
            hashTable->theList[i] = (List) malloc(sizeof(struct ListNode));
            hashTable->theList[i]->element = 0;
        }
        
        while(1) {
            fscanf(inputFile, "%s", temp);
            
            if(strcmp(temp, "i") == 0) {
                fscanf(inputFile, "%d", &value);
                insert(hashTable, value, sol, outputFile);
            } else if(strcmp(temp, "d") == 0) {
                fscanf(inputFile, "%d", &value);
                delete(hashTable, value, sol, outputFile);
            } else if(strcmp(temp, "f") == 0) {
                fscanf(inputFile, "%d", &value);
                int temp = find(hashTable, value, sol);
                if(temp == 0)
                    fprintf(outputFile, "Not found\n");
                else {
                    int index = findForDelete(hashTable, value, sol);
                    fprintf(outputFile, "Found index %d\n", index);
                }
            } else if(strcmp(temp, "p") == 0) {
                print(hashTable, outputFile);
                fprintf(outputFile, "\n");
            } else if(strcmp(temp, "q") == 0) {
                fprintf(outputFile, "\n");
                
                for(int i = 0; i < size; i++) {
                    free(hashTable->theList[i]);
                }
                free(hashTable->theList);
                free(hashTable);
                
                break;
            } else {
                fprintf(outputFile, "No Command.\n");
            }
        }
    }
    return 0;
}

void insert(HashTable h, int value, int solution, FILE* file) {
    if(find(h, value, solution) == 0) {
        int index = findForInsert(h, value, solution);
        h->theList[index]->element = value;
        fprintf(file, "Insert %d\n", value);
    } else {
        fprintf(file, "Already exists\n");
    }
}

void delete(HashTable h, int value, int solution, FILE* file) {
    if(find(h, value, solution) == 0) {
        fprintf(file, "%d not exists\n", value);
    } else {
        int index = findForDelete(h, value, solution);
        h->theList[index]->element = 0;
        fprintf(file, "Deleted %d\n", value);
    }
}

int find(HashTable h, int value, int solution) {
    int i = 0;
    int size = h->tableSize;
    int index, tmp;
    
    while(1) {
        index = hash(value, size, i, solution);
        tmp = h->theList[index]->element;
        if(tmp == 0) {
            return 0;
        }
        
        if(tmp == value) {
            return value;
        }
        
        i++;
    }
}

void print(HashTable h, FILE* file) {
    int size = h->tableSize;
    for(int i = 0; i < size; i++) {
        fprintf(file, "%d ", h->theList[i]->element);
    }
}

int hash(int value, int size, int i, int solution) {
    if(solution == 1) {
        return (value + i) % size;
    } else if(solution == 2) {
        return (value + i*i) % size ;
    } else if(solution == 3) {
        return (value + i*(7 - (value % 7))) % size;
    } else {
        return -1;
    }
}

int findForInsert(HashTable h, int value, int solution) {
    int i = 0;
    int size = h->tableSize;
    int index, tmp;
    
    while(1) {
        index = hash(value, size, i, solution);
        tmp = h->theList[index]->element;
        if(tmp == 0) {
            return index;
        }
        i++;
    }
}

int findForDelete(HashTable h, int value, int solution) {
    int i = 0;
    int size = h->tableSize;
    int index, tmp;
    
    while(1) {
        index = hash(value, size, i, solution);
        tmp = h->theList[index]->element;
        
        if(tmp == value) {
            return index;
        }
        
        i++;
    }
}
