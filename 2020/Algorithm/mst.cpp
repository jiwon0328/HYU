//2019000982_leejiwon_11802

#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, pair<int, int> > pp;

priority_queue < pp, vector<pp>, greater<pp> > input;
vector<pp> output;
int* parent = (int*) malloc(sizeof(int) * 1000);

int findParent(int x);
void Union(int x, int y);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i < n + 1; i++) {
        parent[i] = i;
    }
    
    int x, y, w;
    for (int i = 1; i < m + 1; i++) {
        scanf("%d %d %d", &x, &y, &w);
        input.push(make_pair(w, make_pair(x, y)));
    }

    while (!input.empty()) {
        int a, b;
        
        a = input.top().second.first;
        b = input.top().second.second;

        if (findParent(a) == findParent(b)) {
            input.pop();
        } else {
            Union(a, b);
            output.push_back(input.top());
            input.pop();
        }
    }
    
    printf("%lu\n", output.size());

    for(int i = 0; i < output.size(); i++) {
        printf("%d %d %d\n", output[i].second.first, output[i].second.second, output[i].first);
    }
}

int findParent(int x) {
    if (parent[x] == x) {
        return x;
    }
    return parent[x] = findParent(parent[x]);
}

void Union(int x, int y) {
    parent[findParent(x)] = findParent(y);
}
