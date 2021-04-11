#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

typedef struct {
    char* studentID;
    char* studentName;
} ElementType;

struct Node {
    ElementType element;
    PtrToNode next;
};

void Insert (ElementType X, List L, Position P, FILE * f);
void Delete (ElementType X, List L, FILE * f);
int IsEmpty (List L);
Position Find (ElementType X, List L);
void PrintList (List L, FILE * f);

int main(int argc, const char * argv[]) {
    FILE * ip = fopen("input.txt", "r");
    FILE * op = fopen("output.txt", "w");
    
    if(ip == NULL) {
        printf("FILE OPEN ERROR\n");
        return 0;
    }
    
    List list = (List)malloc(sizeof(struct Node));
    list->next = NULL;
    Position p = list;
    ElementType data;
    
    char tmp[100];
    
    while(fscanf(ip, "%s", tmp) != EOF) {
        data.studentID = (char*)malloc(sizeof(char)*30);
        data.studentName = (char*)malloc(sizeof(char)*30);
        char firstName[30], lastName[30];
        
        if(strcmp(tmp, "i") == 0) {
            fscanf(ip, "%s", data.studentID);
            fscanf(ip, "%s", firstName);
            fscanf(ip, "%s", lastName);
            strcat(firstName, " ");
            strcat(firstName, lastName);
            strcpy(data.studentName, firstName);
            
            Insert(data, list, p, op);
        }
        else if(strcmp(tmp, "d") == 0) {
            fscanf(ip, "%s", data.studentID);
            Delete(data, list, op);
        }
        else if(strcmp(tmp, "f") == 0) {
            fscanf(ip, "%s", data.studentID);
            Position findData = Find(data, list)->next;
            if(findData == NULL) {
                fprintf(op, "Find %s Failed. There is no student ID\n", data.studentID);
            }
            else {
                fprintf(op, "Find Success : %s %s\n", findData->element.studentID, findData->element.studentName);
            }
        }
        else if(strcmp(tmp, "p") == 0) {
            PrintList(list, op);
        }
        else {
            fprintf(op, "Command Error/n");
            return 0;
        }
    }
    free(list);
    free(data.studentName);
    free(data.studentID);
    fclose(ip);
    fclose(op);
}

void Insert (ElementType x, List l, Position p, FILE * f) {
    Position tmpCell;
    
    tmpCell = malloc(sizeof(struct Node));
    if(tmpCell == NULL) {
        fprintf(f, "OUT OF SPACE\n");
        return;
    }
    
    if(Find(x, l)->next != NULL) {
        fprintf(f, "Insertion Failed. ID %s already exists.\n", x.studentID);
        return;
    }

    tmpCell->element = x;
    tmpCell->next = p->next;
    p->next = tmpCell;
    
    fprintf(f, "Insertion Success : %s\n", x.studentID);
    fprintf(f, "Current List > ");
    
    Position tmp = l->next;
    fprintf(f, "%s %s", tmp->element.studentID, tmp->element.studentName);
    tmp = tmp->next;
    
    while(tmp != NULL) {
        fprintf(f, " - %s %s", tmp->element.studentID, tmp->element.studentName);
        tmp = tmp->next;
    }
    fprintf(f, "\n");
    
}

void Delete (ElementType x, List l, FILE * f) {
    Position p = Find(x, l);
    Position wantToDelete;
    if(p->next == NULL) {
        fprintf(f, "Deletion Failed : Student ID %s is not in the list.\n", x.studentID);
        return;
    }
    wantToDelete = p->next;
    p->next = wantToDelete->next;
    free(wantToDelete);
    
    fprintf(f, "Deletion Success : %s\n", x.studentID);
    fprintf(f, "Current List > ");
    
    Position tmp = l->next;
    fprintf(f, "%s %s", tmp->element.studentID, tmp->element.studentName);
    tmp = tmp->next;
    
    while(tmp != NULL) {
        fprintf(f, " - %s %s", tmp->element.studentID, tmp->element.studentName);
        tmp = tmp->next;
    }
    fprintf(f, "\n");
}

Position Find (ElementType x, List l) {
    Position p;
    p = l;
    while(p->next != NULL && strcmp(p->next->element.studentID, x.studentID) != 0) {
        p = p->next;
    }
    return p;
}

void PrintList (List L, FILE * f) {
    Position tmp = L->next;
    fprintf(f, "-----LIST-----\n");
    while(tmp != NULL) {
        fprintf(f, "%s ", tmp->element.studentID);
        fprintf(f, "%s\n", tmp->element.studentName);
        tmp = tmp->next;
    }
    fprintf(f, "--------------\n");
}
