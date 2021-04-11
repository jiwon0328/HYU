//Template
#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int compare(int a, int b){
    if(a > b)
    	return 1;
    else 
       	return -1;
}

void bubbleSort(int* array) {
    int tmp;
    
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE - 1; j++) {
            if(compare(*(array + j), *(array + j + 1)) == 1) {
                tmp = *(array +j + 1);
                *(array +j + 1) = *(array + j);
                *(array + j) = tmp;
            }
            else
                continue;
        }
    }
}


int main(){
    int n_array[SIZE] = {2,-9, 10, 15, 1, 3, -12, 5, 4, 1};
    
    printf("BEFORE : {");
    for(int i = 0; i < SIZE; i++) {
        printf("%d ", n_array[i]);
    }
    printf("}\n\n");
    
    bubbleSort(n_array);

    printf("AFTER : {");
    for(int i = 0; i < SIZE; i++) {
        printf("%d ", n_array[i]);
    }
    printf("}\n");

    return 0;
}
