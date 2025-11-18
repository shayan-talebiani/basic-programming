#include <stdio.h>

int main(){

    long long num;

    scanf("%lld", &num);

    long long powerConter = 0;
    long long iPower2 = 0;
    int firstTime = 1;


    for (long long i = 2; i <= num ; i++){

        iPower2 = i * i;

        if (iPower2 > num && firstTime == 1){
            printf("%lld", num);
            break;
        }else if(iPower2 > num && num != 1){
            printf(" * %lld", num);
            break;
        }
        
        
        powerConter = 0;

        while (num % i == 0){
            
            num /= i;
            powerConter += 1;

            if (num % i != 0){

                if (firstTime == 1){

                    if (powerConter == 1){
                        printf("%lld", i);
                    }else{
                        printf("%lld^%lld", i, powerConter);
                    }
                    
                    firstTime = 0;

                }else{

                    if (powerConter == 1){
                        printf(" * %lld", i);
                    }else{
                        printf(" * %lld^%lld", i, powerConter);
                    }
                    
                }
                


                break;
            }
            
        }
        
    }
    

    printf("\n");

    return 0;
}