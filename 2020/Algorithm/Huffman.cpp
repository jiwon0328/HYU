// 2019000982_leejiwon_11802

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

map<string, int> ch;

int huffman;

class node {
public:
    string ch;
    int num;
    node* l;
    node* r;
    int count;

    node() {
        ch = "";
        num = 0;
        l = NULL;
        r = NULL;
        count = 0;
    }

    node& operator=(const node& A);
};

node& node::operator=(const node& A) {

    this->ch = A.ch;
    this->num = A.num;
    this->l = A.l;
    this->r = A.r;
    this->count = A.count;

    return *this;
}

class compare {
public:
    bool operator()(node* a, node* b);
};

bool compare::operator()(node* a, node* b) {
    if (a->num > b->num) {
        return true;
    }
    
    return false;
}

priority_queue<node*, vector<node*>, compare > h;

void huffmanCode(node* n, int count);

int main() {
    int n, total, b;
    string a;
    cin >> n;
    for (int i = 1; i < n + 1; i++) {
        cin >> a >> b;
        ch.insert(make_pair(a, b));
    }
    
    cin >> total;

    int bits = 1;
    int temp = n / 2;
    while (temp) {
        bits++;
        temp = temp / 2;
    }
    
    int fixedLen = bits * total;

    for (map<string, int>::iterator i = ch.begin(); i != ch.end(); i++) {
        node* tmp = new node();
        tmp->ch = i->first;
        tmp->num = i->second;

        h.push(tmp);
    }

    node* root = NULL;
    while (h.size() != 1) {
        node* a = h.top();
        h.pop();
        node* b = h.top();
        h.pop();

        node* compound = new node();
        compound->num = a->num + b->num;
        compound->l = a;
        compound->r = b;
        h.push(compound);
    }
    
    root = h.top();
    huffmanCode(root, 0);

    cout << fixedLen << endl << huffman << endl;

    return 0;
}

void huffmanCode(node* n, int count) {
    if (n == NULL) {
        return;
    }

    n->count = count;
    if (n->ch != "") {
        huffman += ch[n->ch] * n->count;
        return;
    } else {
        huffmanCode(n->l, count + 1);
        huffmanCode(n->r, count + 1);
    }
}
