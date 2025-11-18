#include <stdio.h>

int main(){

    int m;

    long long n;
    long long copyN;

    long long sumDigits;

    long long sumDigitsPower;

    int specificN;

    long long output = 0;

    scanf("%d", &m);

    for(int i = 0; i < m; i++){
        
        scanf("%lld", &n);

        specificN = 0;

        if(n > 0){

            sumDigits = 0; 
            copyN = n;

            while(copyN > 0){

                sumDigits += copyN % 10;

                copyN /= 10;
            }

            sumDigitsPower = 1;

            if (sumDigits == 1 && sumDigits == n){
                
                specificN = 1;
                
            }else if (sumDigits != 1){
                
                while (n > sumDigitsPower){
                
                    sumDigitsPower *= sumDigits;

                    if (sumDigitsPower == n){
                        
                        specificN = 1;
                        break;
                    }
                
                }
            }

        }else if (n == 0){
            
            specificN = 1;
        }
        
        output *= 2;
        output += specificN;
        
    }

    printf("%lld", output);

    return 0;
}