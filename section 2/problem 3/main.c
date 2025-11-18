#include <stdio.h>

int main(){

    int t;

    long long n;
    long long copyN;
    long long reverseN;

    scanf("%d", &t);

    for(int i = 0; i < t; i++){
        
        scanf("%lld", &n);

        copyN = n;
        reverseN = 0;

        while(copyN > 0){

            reverseN *= 10;

            reverseN += copyN % 10;

            copyN /= 10;
        }

        if(reverseN == n){
            printf("Yes\n");
        }else{
            printf("No\n");
        }

    }

    return 0;
}