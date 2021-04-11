// 2019000982_Leejiwon_11802

#include <stdio.h>
#include <stdlib.h>

void bottomUpCutRod(int *p, int n);
void printCutRodSolution(int s[], int *p, int n);

int main(void) {
    int rodLen;
    
    scanf("%d", &rodLen);
    
    int *p = (int*) malloc(sizeof(int) * rodLen);
    p[0] = 0;
    for(int i = 1; i <= rodLen; i++) {
        scanf("%d", &p[i]);
    }
    
    bottomUpCutRod(p, rodLen);
    
    return 0;
}
void bottomUpCutRod(int *p, int n) {
    int q;
    int r[n + 1], s[n + 1];
    r[0] = 0;
    
    for(int j = 1; j <= n; j++) {
        q = -1;
        for(int i = 1; i <= j; i++) {
            if(q < p[i] + r[j - i]) {
                q = p[i] + r[j - i];
                s[j] = i;
            }
        }
        r[j] = q;
    }
    printf("%d\n", r[n]);
    printCutRodSolution((int*) s, p, n);
}

void printCutRodSolution(int s[], int *p, int n) {
    while(n > 0) {
        printf("%d ", s[n]);
        n = n - s[n];
    }
    printf("\n");
}
