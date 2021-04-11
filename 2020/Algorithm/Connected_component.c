//2019000982_leejiwon_11802

#include <stdio.h>
#include <stdlib.h>

typedef struct edge Edge;
struct edge {
    int x, y;
};

int findSet(int e, int* vertexes);
int* unionSet(int x, int y, int* vertexes, Edge* edges);

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    
    Edge *edges = (Edge*) malloc(sizeof(Edge) * m);
    for(int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i].x, &edges[i].y);
    }
    
    int *vertexes = (int*) malloc(sizeof(int) * (n + 1));
    for(int i = 1; i < n + 1; i++) {
        vertexes[i] = i;
    }
    
    int xPer, yPer;
    for(int i = 0; i < m; i++) {
        xPer = findSet(edges[i].x, vertexes);
        yPer = findSet(edges[i].y, vertexes);
        
        if(xPer != yPer)
            vertexes = unionSet(xPer, yPer, vertexes, edges);
    }
    
    int count = 0;
    int *result = (int*) malloc(sizeof(int) * n);
    int tmp;
    int p = 0;
    for(int i = 1; i < n+1; i++) {
        tmp = findSet(i, vertexes);
        for(int i = 0; i < count; i++) {
            if(tmp == result[i]) {
                p = 1;
                break;
            }
        }
        if(p != 1) {
            result[count] = tmp;
            count++;
        }
        p = 0;
    }
    
    printf("%d", count);
    
    free(edges);
    free(vertexes);
    free(result);
    return 0;
}

int findSet(int e, int* vertexes) {
    if(vertexes[e] == e)
        return e;
    else
        return findSet(vertexes[e], vertexes);
}

int* unionSet(int x, int y, int* vertexes, Edge* edges) {
    if(vertexes[x] == x && vertexes[y] == y) {
        vertexes[y] = x;
    }
    else if(vertexes[x] == x && vertexes[y] != y)
        vertexes[x] = vertexes[y];
    else
        vertexes[y] = vertexes[x];
    
    return vertexes;
}
