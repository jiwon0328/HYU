//2019000982_이지원_알고리즘및문제해결기법

#include <stdio.h>
#include <stdlib.h>

void merge(int* arr, int start, int mid, int end);
void mergeSort(int* arr, int l, int r);
int lowerBound(int* arr, int N, int key);
int upperBound(int* arr, int N, int key);

int main(void) {
    int n;
    int m;
    int k;

    scanf("%d%d%d", &n, &m, &k);

    int* array = (int*) malloc(sizeof(int) * n);

    int** range = (int**) malloc(sizeof(int*) * 2);
    range[0] = (int*) malloc(sizeof(int) * k);
    range[1] = (int*) malloc(sizeof(int) * k);

    for (int i = 0; i < k; i++) {
        scanf("%d%d", &range[0][i], &range[1][i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    mergeSort(array, 0, n - 1);

    for (int i = 0; i < k; i++) {
        int start = lowerBound(array, n, range[0][i]);
        int end = upperBound(array, n, range[1][i]);
        int tmp = 0;
        if (start == n) tmp = 0;
        else tmp = end - start;

        printf("%d\n", tmp);
    }
}

void mergeSort(int* array, int start, int end) {
    if (end <= start)
        return;

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

int lowerBound(int* array, int n, int key) {
    int left = 0;
    int right = n - 1;

    int tmp = n;

    while (left <= right) {
        int mid = (left + right) / 2;
        
        if (key <= array[mid]) {
            right = mid - 1;
            tmp = mid;
        } else if (key > array[mid]) {
            left = mid + 1;
        }
    }

    return tmp;
}

int upperBound(int* array, int n, int key) {
    int left = 0;
    int right = n - 1;

    int tmp = n;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (key < array[mid]) {
            right = mid - 1;
            tmp = mid;
        }
        else if (key >= array[mid]) {
            left = mid + 1;
        }
    }

    return tmp;
}
