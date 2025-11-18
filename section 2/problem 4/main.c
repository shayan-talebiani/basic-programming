#include <stdio.h>

int main(){

    int m;

    long long n;
    long long copyN;

    long long sumDigits;

    long long output;

    scanf("%d", &m);

    for(int i = 0; i < m; i++){
        
        scanf("%lld", &n);

        if(n < 0){
            copyN = -n;
        }

        sumDigits = 0; 

        while(copyN > 0){

            sumDigits += copyN % 10;

            copyN /= 10;
        }



    }

    return 0;
}