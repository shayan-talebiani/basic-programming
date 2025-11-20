#include <stdio.h>

int main(){

    int n;
    unsigned long long k;

    int cDigit;

    int w1Digit;
    int w2Digit;     

    int n1Digit;
    int n2Digit;   

    int nW1Digit;
    int nW2Digit; 
    
    int nE1Digit;
    int nE2Digit;  

    int founded;

    int firstTime = 1;

    while (n != -1 || firstTime == 1){
        
        firstTime = 0;
        
        founded = 0;

        scanf("%d", &n);

        if (n == -1){
            
            printf("Congrats, Dory is home.");
            break;
        }
        
        scanf("%llu", &k);

        for (int i = 0; i < n; i++){
            
            for (int j = 0; j < n; j++){

                cDigit = (k >> (j + i * n)) & 1;

                if (cDigit == 1){
                    
                    if (i < n - 2){
                        
                        n1Digit = (k >> (j + (i + 1) * n)) & 1;

                        if(n1Digit == 1){

                            n2Digit = (k >> (j + (i + 2) * n)) & 1;

                            if(n2Digit == 1){
                                
                                founded = 1;
                                printf("Yes\n");
                                break;
                            }
                        }

                    }

                    if (j < n - 2){
                        
                        w1Digit = (k >> (j + 1 + i * n)) & 1;

                        if(w1Digit == 1){

                            w2Digit = (k >> (j + 2 + i * n)) & 1;

                            if(w2Digit == 1){
                                
                                founded = 1;
                                printf("Yes\n");
                                break;
                            }
                        }

                    }   
                    
                    if (j < n - 2 && i < n - 2){
                        
                        nW1Digit = (k >> (j + 1 + (i + 1) * n)) & 1;

                        if(nW1Digit == 1){

                            nW2Digit = (k >> (j + 2 + (i + 2) * n)) & 1;

                            if(nW2Digit == 1){
                                
                                founded = 1;
                                printf("Yes\n");
                                break;
                            }
                        }

                    }  

                    if (j > 1 && i < n - 2){
                        
                        nE1Digit = (k >> (j - 1 + (i + 1) * n)) & 1;

                        if(nE1Digit == 1){

                            nE2Digit = (k >> (j - 2 + (i + 2) * n)) & 1;

                            if(nE2Digit == 1){
                                
                                founded = 1;
                                printf("Yes\n");
                                break;
                            }
                        }

                    }  



                }

            }

            if(founded == 1){
                break;
            }
        }

        if(founded == 0){
            printf("No\n");
        }        
        


    } 


    return 0;
}