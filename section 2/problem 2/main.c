#include <stdio.h>

int main(){

    int m;
    long long n;

    int firstPrint = 1;

    scanf("%d", &m);

    for(int i = 0; i < m; i++){
        
        scanf("%lld", &n);

        if(n < 0){
            n = -n;
        }

        firstPrint = 1;

        while(n > 2){

            if(n % 3 == 0){
                printf("Oooh that’s good!\n");
                firstPrint = 0;
                break;
            }else{
                n /= 10;
            }

        }

        if(firstPrint == 1){
            printf("Oooh delom shikast!\n");
        }

    }

    return 0;
}