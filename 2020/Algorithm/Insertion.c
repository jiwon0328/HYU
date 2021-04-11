//2019000982_Leejiwon_11802

#include <stdio.h>

int main(void) {
    int num;
    
    scanf("%d", &num);
    int array[num];
    
    for(int i = 1; i < num + 1; i++) {
        scanf("%d", &array[i]);
    }
    
    int key, i;
    
    for(int j = 2; j < num + 1; j++) {
        key = array[j];
        
        i = j - 1;
        
        while(i > 0 && array[i] < key) {
            array[i + 1] = array[i];
            i = i - 1;
        }
        
        array[i + 1] = key;
    }
    
    for(int i = 1; i < num + 1; i++) {
        printf("%d\n", array[i]);
    }
    
    return 0;
}
