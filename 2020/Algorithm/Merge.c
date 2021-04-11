//2019000982_Leejiwon_11802

#include <stdio.h>

void mergeSort(int array[], int tmpArray[], int p, int r);
void merge(int array[], int tmpArray[], int p, int q, int r);

int main(void) {
    int num;
    scanf("%d", &num);
    
    int array[num];
    for(int i = 1; i < num + 1; i++) {
        scanf("%d", &array[i]);
    }
    
    int first = 1;
    int end = num;
    int tmpArray[num];
    
    mergeSort(array, tmpArray, first, end);
    
    for(int i = 1; i < num + 1; i++) {
        printf("%d\n", tmpArray[i]);
    }
    
    
    return 0;
}

void mergeSort(int array[], int tmpArray[], int p, int r) {
    int q;
    if(p < r) {
        q = (p + r)/2;
        mergeSort(array, tmpArray, p, q);
        mergeSort(array, tmpArray, q + 1, r);
        merge(array, tmpArray, p, q + 1, r);
    }
}

void merge(int array[], int tmpArray[], int p, int q, int r) {
//    int n1 = q - p + 1;
//    int n2 = r - q;
//    int left[n1 +1], right[n2 + 1];
//
//    for(int i = 1; i < n1; i++)
//        left[i] = array[p + i - 1];
//
//    for(int j = 1; j < n2; j++)
//        right[j] = array[q + j];
//
//    left[n1 + 1] = 100;
//    right[n2 + 1] = 100;
//
//    int i = 1;
//    int j = 1;
//
//    for(int k = p; k < r; k++) {
//        if(left[i] >= right[j]) {
//            array[k] = left[i];
//            i = i + 1;
//        } else if(left[k] == right[j]) {
//            j = j + 1;
//        }
//    }
    
    int leftEnd, numElements, tmpPos;
    leftEnd = q - 1;
    tmpPos = p;
    numElements = r - p + 1;
    
    while(p <= leftEnd && q <= r) {
        if(array[p] >= array[q])
            tmpArray[tmpPos++] = array[p++];
        else
            tmpArray[tmpPos++] = array[q++];
    }
    
    while(p <= leftEnd)
        tmpArray[tmpPos++] = array[p++];
    while(q <= r)
        tmpArray[tmpPos++] = array[q++];
    
    for(int i = 0; i < numElements; i++, r--) {
        array[r] = tmpArray[r];
    }
    
}
