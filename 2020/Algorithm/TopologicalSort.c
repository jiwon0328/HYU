//2019000982_leejiwon_11802

#include <stdio.h>
#include <stdlib.h>
#define WHITE 0;
#define GRAY 1;
#define BLACK 2;

typedef struct vertex Vertex;
struct vertex {
    int name;
    int color;
    int pi;
    int d;
    int f;
    int *adj;
};

typedef struct edge Edge;
struct edge {
    int x, y;
};

Vertex* adj(Vertex *v, int m, Edge* edges);
void dfs(Vertex *v, int n, int m);
int dfsVisit(Vertex *v, int index, int n);
int isDag(Vertex *v, int n);
void printTopological(Vertex *v, int n);

int _time = 0;

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    
    Edge* edges = (Edge*) malloc(sizeof(Edge) * m);
    for(int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i].x, &edges[i].y);
    }

    Vertex* vertexes = (Vertex*) malloc(sizeof(Vertex) * (n + 1));
    for(int i = 1; i < n + 1; i++) {
        vertexes[i].pi = 0;
        vertexes[i].name = i;
        vertexes[i].adj = (int*) malloc(sizeof(int) * (n + 1));
        for(int j = 1; j < n + 1; j++) {
            vertexes[i].adj[j] = 0;
        }
    }
    
    vertexes = adj(vertexes, m, edges);
    
    dfs(vertexes, n, m);
    
    int dag = isDag(vertexes, n);
    printf("%d\n", dag);
    
    printTopological(vertexes, n);
    
    for(int i = 1; i < n + 1; i++) {
        free(vertexes[i].adj);
    }
    free(vertexes);
    free(edges);
    
    return 0;
}

Vertex* adj(Vertex *vertexes, int m, Edge* edges) {
    int x, y;
    
    for(int i = 0; i < m ; i++) {
        x = edges[i].x;
        y = edges[i].y;
        
        vertexes[x].adj[y] = 1;
    }
    
    return vertexes;
}

void dfs(Vertex *vertexes, int n, int m) {
    for(int i = 1; i < n + 1; i++) {
        vertexes[i].color = 0;
        vertexes[i].pi = 0;
    }
    
    int tmp;
    
    for(int i = 1; i < n + 1; i++) {
        if(vertexes[i].color == 0) {
            tmp = dfsVisit(vertexes, i, n);
        }
    }
}

int dfsVisit(Vertex *vertexes, int index, int n) {
    _time = _time + 1;
    vertexes[index].d = _time;
    vertexes[index].color = 1;
    
    int *adj = vertexes[index].adj;
    
    for(int i = 1; i < n + 1; i++) {
        if(adj[i] == 1) {
            if(vertexes[i].color != 2) {
                vertexes[i].pi = vertexes[index].name;
            }
            if(vertexes[i].color == 0) {
                dfsVisit(vertexes, i, n);
            }
        }
    }
    
    vertexes[index].color = BLACK;
    _time = _time + 1;
    vertexes[index].f = _time;
    
    return vertexes[index].name;
}

int isDag(Vertex *v, int n) {
    int result = 1;
    for(int i = n; i > 0; i--) {
        Vertex tmp = v[i];
        int *pis = (int*) malloc(sizeof(int) * n);
        int count = 0;
        while(tmp.pi != 0) {
            tmp = v[tmp.pi];
            
            for(int i = 0; i < count; i++) {
                if(tmp.name == pis[i]) {
                    result = 0;
                    break;
                }
            }
            pis[count] = tmp.name;
            count++;
            
            if(result == 0)
                break;
            
        }
        
    }
    
    return result;
}

void printTopological(Vertex *v, int n) {
    for(int j = n * 2; j > 0 ; j--) {
        for(int i = 1; i < n + 1; i++) {
            if(v[i].f == j)
                printf("%d ", i);
        }
    }
}
