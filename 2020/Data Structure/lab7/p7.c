#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int e1;
    int e2;
}Edge;

int Find(int *set, int x);
void Union(int *set, int r1, int r2);
int Pick(int num);

int main(void) {
    srand((unsigned int) time(NULL));
    
    FILE * inputFile = fopen("input.txt", "r");
    FILE * outputFile = fopen("output.txt", "w");
    
    if(inputFile == NULL) {
        fprintf(outputFile, "FILE OPEN ERROR!\n");
        return 0;
    }
    
    int num;
    fscanf(inputFile, "%d", &num);
    int numSquare = num * num;
    
    //Init Edge Set
    int totalEdge = 2 * num * (num - 1);
    Edge edge[totalEdge + 1];
    edge[0].e1 = 0;
    edge[0].e2 = 0;
    
    // 가로 저장
    for(int i = 1; i <= num; i++) {
        for(int j = 1; j < num; j++) {
            int index = (num - 1) * (i - 1) + j;
            edge[index].e1 = (num *(i - 1)) + j;
            edge[index].e2 = (num *(i - 1)) + j + 1;
        }
    }
    //세로 저장
    for(int i = 1; i <=num; i++) {
        for(int j = 1; j < num; j++) {
            int index = (totalEdge / 2) + ((num - 1) * (i - 1)) + j;
            edge[index].e1 = ((j - 1) * num) + i;
            edge[index].e2 = j * num + i;
        }
    }
    
    int set[numSquare];
    for(int i = 1; i <= (numSquare); i++)
        set[i] = 0;
    
    
    //미로 만들기
    int byun = (2 * num) + 1;
    char maze[byun][byun];
    
    for(int i = 0; i < byun; i++) {
        for(int j = 0; j < byun; j++) {
            if(i % 2 == 0) {
                if(j % 2 == 0)
                    maze[i][j] = '+';
                else
                    maze[i][j] = '-';
            } else {
                if(j % 2 == 0)
                    maze[i][j] = '|';
                else
                    maze[i][j] = ' ';
            }
            maze[1][0] = ' ';
            maze[byun - 2][byun - 1] = ' ';
        }
    }
    
    while(1) {
        
        int pickedIndex = Pick(totalEdge);
        Edge pickedEdge = edge[pickedIndex];
        
        
        while(pickedEdge.e1 == 0 || pickedEdge.e2 == 0) {
            pickedIndex = Pick(totalEdge);
            pickedEdge = edge[pickedIndex];
        }
        
        edge[pickedIndex].e1 = 0;
        edge[pickedIndex].e2 = 0;
    
        
        int root1 = Find(set, pickedEdge.e1);
        int root2 = Find(set, pickedEdge.e2);
        
        
        int sero = (pickedEdge.e1 - 1) / num + 1;
        int garo = (pickedEdge.e1 - 1) % num + 1;
        
        if(root1 != root2) {
            Union(set, root1, root2);
            if(pickedEdge.e2 == pickedEdge.e1 + 1) {
                maze[(2 * sero) - 1][2 * garo] = ' ';
            } else {
                maze[2 * sero][(2 * garo) - 1] = ' ';
            }
        }
        
        int first = Find(set, 1);
        int end = Find(set, numSquare);
        
        if(first == end) {
            for(int i = 0; i< byun; i++) {
                for(int j = 0; j < byun; j++) {
                    fprintf(outputFile, "%c", maze[i][j]);
                }
                fprintf(outputFile, "\n");
            }
            break;
        }
        else
            continue;
    }
    
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

int Find(int *set, int x) {
    if(set[x] <= 0) {
        return x;
    }
    else
        return set[x] = Find(set, set[x]);
}

void Union(int *set, int r1, int r2) {
    if(set[r1] < set[r2])
        set[r1] = r2;
    else {
        if(set[r2] == set[r1])
            set[r1]--;
        set[r2] = r1;
    }
}

int Pick(int num) {
    return rand() % num + 1;
}
