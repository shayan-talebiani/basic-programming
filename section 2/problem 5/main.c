#include <stdio.h>

int main(){

    int n;
    int k;

    int firstTime = 1;

    while (n != -1 || firstTime == 1){
        
        firstTime = 0;
        
        scanf("%d", &n);

        if (n == -1){
            
            printf("Congrats, Dory is home.");
            break;
        }
        
        scanf("%d", &k);



    } 


    return 0;
}