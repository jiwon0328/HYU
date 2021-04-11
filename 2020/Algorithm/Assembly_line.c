//2019000982_Leejiwon_11802

#include <stdio.h>
#include <stdlib.h>

int fastestWay(int *s1, int *s2, int *l1, int *l2, int *a1, int *a2, int *t1, int *t2, int *e, int *x, int n);
void printStation(int *l1, int *l2, int last, int n);

int main(void) {
    int stationNum;
    int *e = (int*) malloc(sizeof(int) * 2);
    int *x = (int*) malloc(sizeof(int) * 2);
    
    scanf("%d", &stationNum);
    scanf("%d %d", &e[0], &e[1]);
    scanf("%d %d", &x[0], &x[1]);
    
    int *a1 = (int*) malloc(sizeof(int) * stationNum);
    int *a2 = (int*) malloc(sizeof(int) * stationNum);
    
    int *t1 = (int*) malloc(sizeof(int) * (stationNum - 1));
    int *t2 = (int*) malloc(sizeof(int) * (stationNum - 1));
    
    int *s1 = (int*) malloc(sizeof(int) * (stationNum + 1));
    int *s2 = (int*) malloc(sizeof(int) * (stationNum + 1));
    
    int *l1 = (int*) malloc(sizeof(int) * (stationNum + 1));
    int *l2 = (int*) malloc(sizeof(int) * (stationNum + 1));
    
    for(int i = 0; i < stationNum; i++) {
        scanf("%d", &a1[i]);
    }
    for(int i = 0; i < stationNum; i++) {
        scanf("%d", &a2[i]);
    }
    for(int i = 0; i < stationNum - 1; i++) {
        scanf("%d", &t1[i]);
    }
    for(int i = 0; i < stationNum - 1; i++) {
        scanf("%d", &t2[i]);
    }
    
    int time =fastestWay(s1, s2, l1, l2, a1, a2, t1, t2, e, x, stationNum);
    
    printf("%d\n", time);
    
    printStation(l1, l2, l1[stationNum], stationNum);

    
    // free
    free(e);
    free(x);
    free(a1);
    free(a2);
    free(t1);
    free(t2);
    free(s1);
    free(s2);
    free(l1);
    free(l2);
    
    return 0;
}

int fastestWay(int *s1, int *s2, int *l1, int *l2, int *a1, int *a2, int *t1, int *t2, int *e, int *x, int n) {
    s1[0] = e[0] + a1[0];
    s2[0] = e[1] + a2[0];
    
    for(int i = 1; i < n; i++) {
        if(s1[i - 1] <= (s2[i - 1] + t2[i - 1])) {
            s1[i] = s1[i - 1] + a1[i];
            l1[i] = 1;
        } else {
            s1[i] = s2[i - 1] + t2[i - 1] + a1[i];
            l1[i] = 2;
        }
        
        if(s2[i - 1] <= (s1[i - 1] + t1[i - 1])) {
            s2[i] = s2[i - 1] + a2[i];
            l2[i] = 2;
        } else {
            s2[i] = s1[i - 1] + t1[i - 1] + a2[i];
            l2[i] = 1;
        }
    }
    
    if(s1[n - 1] + x[0] <= s2[n - 1] + x[1])
        l1[n] = 1;
    else
        l1[n] = 2;
    
    l2[n] = 0;
    s1[n] = s1[n - 1] + x[0];
    s2[n] = s2[n - 1] + x[1];
    
    if(s1[n] >= s2[n])
        return s2[n];
    else
        return s1[n];
}

void printStation(int *l1, int *l2, int last, int n) {
    int *order = (int*) malloc(sizeof(int) * n);
    int i = last;
    
    order[n - 1] = i;
    
    for(int j = n; j > 1; j--) {
        if(i == 1)
            i = l1[j - 1];
        else
            i = l2[j - 1];
        order[j - 2] = i;
    }
    
    for(int i = 0; i < n; i++) {
        printf("%d %d\n", order[i], i + 1);
    }
    
    free(order);
}
