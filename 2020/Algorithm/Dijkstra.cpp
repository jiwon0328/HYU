// 2019000982_leejiwon_11802

#include <cstdio>
#include <limits.h>
#include <vector>

using namespace std;

class Vertex {
public:
    int name;
    bool s;
    vector<pair<int, int> > edges;

    Vertex() {
        this->name = INT_MAX;
        this->start = false;
    }
};

Vertex* vertexes;

void dijkstra(int index);
int min(int n);

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);

    vertexes = new Vertex[vertex];
    vertexes[0].name = 0;

    for (int i = 0; i < m; i++) {
       int x, y, w;
       scanf("%d %d %d", &x, &y, &w);

       vertexes[x - 1].edges.push_back({ y - 1, w });
    }

    dijkstra(0);
    vertexes[0].start = true;

    int index;
    for (int i = 1; i < n; i++) {
       index = min(n);

       if (index != -1) {
          dijkstra(index);
          vertexes[index].start = true;
        }
    }

    index = 0;

    for (int i = 1; i < n; i++) {
       if (vertexes[i].name > vertexes[index].name) {
          index = i;
        }
    }

    printf("%d\n", vertexes[index].name);

    return 0;
}

void dijkstra(int index) {
    for (int i = 0; i < vertexes[index].edges.size(); i++) {
        int y = vertexes[index].edges[i].first;
        int w = vertexes[index].edges[i].second;
        int name = vertexes[index].name;
        if (vertexes[y].name > name + w) {
            vertexes[y].name = name + w;
        }
    }
}

int min(int n) {
    int index = -1;

    for (int i = 0; i < n; i++) {
        if (vertexes[i].start) {
            continue;
        }

        if (index == -1 || vertexes[i].name < vertexes[index].name) {
            index = i;
        }
    }

    return index;
}
