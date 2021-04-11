//2019000982_Leejiwon_11802

#include <stdio.h>
#include <stdlib.h>

typedef struct HeapStruct* Heap;
struct HeapStruct {
    int capacity;
    int size;
    int* elements;
};

Heap makeNode(int capacity);
void insert(int x, Heap h);
int find(int x, Heap h);
void print(Heap h);
int pop(Heap h);

int main() {

    int capacity, n;
    scanf("%d%d", &capacity, &n);

    Heap heap = makeNode(capacity);

    int element;
    while (capacity--) {
        scanf("%d", &element);
        insert(element, heap);
    }

    while (n--) {
        printf("%d ", pop(heap));
    }
    printf("\n");

    for (int i = 1; i <= heap->size; i++) {
        printf("%d ", heap->elements[i]);
    }
    printf("\n");

    return 0;
}

Heap makeNode(int capacity) {
    Heap h = (Heap)malloc(sizeof(struct HeapStruct));
    h->capacity = capacity;
    h->elements = (int*)malloc(sizeof(int) * (capacity + 1));
    h->size = 0;
    return h;
}

void insert(int x, Heap h) {
    if (h->size == h->capacity)
        printf("heap is full\n");

    else {
        int i;
        h->size++;
        for (i = h->size; i / 2 > 0 && h->elements[i / 2] < x; i /= 2) {
            h->elements[i] = h->elements[i / 2];
        }
        h->elements[i] = x;
    }
}

int find(int x, Heap h) {
    for (int i = 1; i <= h->size; i++) {
        if (h->elements[i] == x) {
            return 1;
        }
    }
    return 0;
}

void Print(Heap h) {
    for (int i = 1; i <= h->size; i++) {
        printf("%d ", h->elements[i]);
    }
    printf("\n");
}

int pop(Heap h) {

    int ret = h->elements[1];

    int key = h->elements[h->size];
    h->elements[1] = key;
    h->size--;

    int i = 1;
    while ((i * 2 <= h->size && h->elements[i * 2] > key) || (i * 2 + 1 <= h->size && h->elements[i * 2 + 1] > key)) {
        if (i * 2 + 1 <= h->size && h->elements[i * 2] < h->elements[i * 2 + 1]) {
            h->elements[i] = h->elements[i * 2 + 1];
            i = i * 2 + 1;
        } else {
            h->elements[i] = h->elements[i * 2];
            i = i * 2;
        }
    }
    h->elements[i] = key;

    return ret;
}
