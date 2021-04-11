//2019000982_Leejiwon_11802

#include <stdio.h>
#include <stdlib.h>

void merge(int* arr, int start, int mid, int end);
void mergeSort(int* arr, int l, int r);
int binarySearch(int* arr, int N, int key);


int main(void) {
    int n, m;
    scanf("%d%d", &n, &m);
    int* array1 = (int*) malloc(sizeof(int) * n);
    int* array2 = (int*) malloc(sizeof(int) * m);

    for (int i = 0; i < n; i++) {
        scanf("%d", &array1[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &array2[i]);
    }

    mergeSort(array1, 0, n - 1);
    mergeSort(array2, 0, m - 1);

    int tmp = 0;
    if (n <= m) {
        for (int i = 0; i < n; i++) {
            if (binarySearch(array2, m, array1[i]) == 1)
                tmp++;
        }
    }
    else {
        for (int i = 0; i < m; i++) {
            if (binarySearch(array1, n, array2[i]) == 1)
                tmp++;
        }
    }
    
    printf("%d\n", tmp);
    
    free(array1);
    free(array2);
    
    return 0;
}

void mergeSort(int* array, int start, int end) {
    if (end <= start) return;

    int mid = (start + end) / 2;

    mergeSort(array, start, mid);
    mergeSort(array, mid + 1, end);
    merge(array, start, mid, end);
}

void merge(int* array, int start, int mid, int end) {
    int* sortedArray = (int*) malloc(sizeof(int) * (end - start + 1));

    int i = start;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= end) {
        if (array[i] < array[j]) {
            sortedArray[k++] = array[i++];
        } else {
            sortedArray[k++] = array[j++];
        }
    }

    if (i > mid) {
        for (int l = j; l <= end; l++) {
            sortedArray[k++] = array[l];
        }
    }
    
    if (j > end) {
        for (int l = i; l <= mid; l++) {
            sortedArray[k++] = array[l];
        }
    }

    int index = 0;
    
    for (int l = start; l <= end; l++) {
        array[l] = sortedArray[index++];
    }
}

int binarySearch(int* array, int n, int key) {
    int left = 0;
    int right = n - 1;

    int tmp = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        
        if (key < array[mid]) {
            right = mid - 1;
        } else if (key > array[mid]) {
            left = mid + 1;
        } else if (key == array[mid]) {
            return tmp = 1;
        }
    }

    return tmp;
}
