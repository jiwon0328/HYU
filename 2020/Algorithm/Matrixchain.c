//2019000982_Leejiwon_11802

#include <stdio.h>
#include <stdlib.h>

void matrixChainOrder(int* p, int n);
void printOptimalParens(int *s, int i, int j, int n);

int main(void) {
    int num;
    scanf("%d", &num);
    int *p = (int*) malloc(sizeof(int) * (num + 1));
    for(int i = 0; i <= num; i++) {
        scanf("%d", &p[i]);
    }
    
    matrixChainOrder(p, num);
    return 0;
}

void matrixChainOrder(int* p, int n) {
    int m[n + 1][n + 1];
    int s[n + 1][n + 1];
    int j, q;
    
    for(int i = 1; i < n + 1; i++) {
        m[i][i] = 0;
    }
    
    for(int l = 2; l <= n; l++) {
        for(int i = 1; i <= n - l + 1; i++) {
            j = i + l - 1;
            m[i][j] = 10000000;
            for(int k = i; k <= j - 1; k++) {
                q = m[i][k] + m[k + 1][j] + p[i - 1]*p[k]*p[j];
                if(q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("%d\n", m[1][n]);
    
    printOptimalParens((int*)s, 1, n, n + 1);
}

void printOptimalParens(int s[], int i, int j, int n) {
    if (i == j)
        printf("%d", i);
    else {
        printf("(");
        printOptimalParens(s, i, *((s + i * n) + j), n);
        printOptimalParens(s, *((s + i * n) + j) + 1, j, n);
        printf(")");
    }
}
