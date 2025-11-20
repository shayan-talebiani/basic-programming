#include <stdio.h>

int main(){
    
    unsigned long long k;
    
    scanf("%llu", k);

    int areaCount = 0;

    int n = 8;

    for (int i = 0; i < n; i++){
        
        for (int j = 0; j < n; j++){

            int digit = (k >> (j + i * n)) & 1;

            if(digit == 0){

                areaCount += 1;
                            
                int deep = 0;

                unsigned long long zeroxlocations0 = 0;
                unsigned long long zeroxlocations1 = 0;
                unsigned long long zeroxlocations2 = 0;

                unsigned long long zeroylocations0 = 0;
                unsigned long long zeroylocations1 = 0;
                unsigned long long zeroylocations2 = 0;

                k += 1 << (j + i * n);
                
                if (deep < 24){
                    zeroxlocations0 += j << (3 * (deep));
                    zeroylocations0 += i << (3 * (deep));
                }else if (deep < 48){
                    zeroxlocations1 += j << (3 * (deep));
                    zeroylocations1 += i << (3 * (deep));
                }else{
                    zeroxlocations2 += j << (3 * (deep));
                    zeroylocations2 += i << (3 * (deep));
                }

                int jCopy = j;
                int iCopy = i;

                int searching = 1;

                int wentDown = 1;


                while (searching == 1){
                    
                    if(wentDown == 1){

                    }else{ 

                    }
                


                }

            }


            

        }
    }
    


    printf("%d", areaCount);

    return 0;
}