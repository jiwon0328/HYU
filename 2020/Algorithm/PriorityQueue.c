//2019000982_Leejiwon_11802

#include <stdio.h>
#include <stdlib.h>

typedef struct Heapstruct Heap;
struct Heapstruct {
    int size;
    int* arr;
};

Heap* createHeap(int);
void heapify(Heap*, int);
int deleteMax(Heap*);
void insert(Heap*, int);

int main() {
    Heap* maxheap = createHeap(100000);
    int* m_arr = (int*) malloc(sizeof(int) * 100000);
    int cnt = 0;
    while(1) {
        int command, num, index;
        scanf("%d", &command);
        
        if(command == 1) {
            scanf("%d", &num);
            
            insert(maxheap, num);
        } else if(command == 2) {
            m_arr[cnt++] = deleteMax(maxheap);
        } else if(command == 3) {
            scanf("%d %d", &index, &num);
            
            maxheap->arr[index] = num;
            
            for (int j = index; j > 0; j /= 2) {
                heapify(maxheap, j);
            }
        } else if(command == 0) {
            for (int j = 0; j < cnt; ++j) {
                printf("%d ", m_arr[j]);
            }
            printf("\n");
            
            for (int j = 1; j <= maxheap->size; ++j) {
                printf("%d ", maxheap->arr[j]);
            }
            printf("\n");
            
            break;
        } else
            break;
    }

    return 0;

}

Heap* createHeap(int size) {
    Heap* tmp;
    tmp = (Heap*) malloc(sizeof(Heap));
    tmp->size = 0;
    tmp->arr = (int*) malloc(sizeof(int) * (size + 1));

    return tmp;
}

void heapify(Heap* Uheap, int n) {
    int child = n * 2;
    int tmp;
    if (Uheap->size >= child) {
        if (child != Uheap->size && Uheap->arr[child] <= Uheap->arr[child + 1]) child++;
        if (Uheap->arr[child] > Uheap->arr[n]) {
            tmp = Uheap->arr[n];
            Uheap->arr[n] = Uheap->arr[child];
            Uheap->arr[child] = tmp;
            heapify(Uheap, child);
        }
    }

}

void insert(Heap* heap, int value) {
    int i;
    for (i = ++heap->size; i / 2 > 0 && heap->arr[i / 2] < value; i /= 2) {
        heap->arr[i] = heap->arr[i / 2];
    }
    
    heap->arr[i] = value;
}

int deleteMax(Heap* heap) {
    int i, child, max, end;
    max = heap->arr[1];
    end = heap->arr[heap->size--];

    for (i = 1; i * 2 <= heap->size; i = child) {
        child = i * 2;
        
        if (child != heap->size && heap->arr[child] <= heap->arr[child + 1])
            child++;
        if (end < heap->arr[child])
            heap->arr[i] = heap->arr[child];
        else
            break;
    }
    
    heap->arr[i] = end;
    
    return max;
}
