#include <stdio.h>
#include <stdlib.h>

int main(void){
	char** pp_data = NULL;
	int n;
	int length;
	int i;

    printf("입력할 문자의 수 : ");
	scanf("%d", &n);

    pp_data = (char**) malloc(sizeof(char*) * n);
    
    printf("입력할 문자의 최대 길이 : ");
    scanf("%d", &length);
    
    for(i = 0; i < n; i++) {
        pp_data[i] = (char*) malloc(sizeof(char) * length);
    }
    
    for(i = 0; i < n; i++) {
        printf("%d번째 문자를 입력하세요 : ", i + 1);
        scanf("%s", pp_data[i]);
    }
    
    printf("결과 : ");
    for(i = 0; i < n; i++) {
        printf("%s ", pp_data[i]);
    }
    printf("\n");
	
    for(i = 0; i < n; i++) {
        free(pp_data[i]);
    }
    
    free(pp_data);

	return 0;
}
