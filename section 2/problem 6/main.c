#include <stdio.h>

int main(){

    int n;
    unsigned long long x;

    int digit;

    int rj;

    long v0;
    long v1;
    long v2;
    long v3;
    long v4;
    long v5;
    long v6;
    long v7;

    long h0;
    long h1;
    long h2;
    long h3;
    long h4;
    long h5;
    long h6;
    long h7;

    long rh0;
    long rh1;
    long rh2;
    long rh3;
    long rh4;
    long rh5;
    long rh6;
    long rh7;

    int numSymmetry;

    scanf("%d", &n);

    for (int t = 0; t < n; t++){

        scanf("%llu", &x);

        v0 = 0;
        v1 = 0;
        v2 = 0;
        v3 = 0;
        v4 = 0;
        v5 = 0;
        v6 = 0;
        v7 = 0;

        h0 = 0;
        h1 = 0;
        h2 = 0;
        h3 = 0;
        h4 = 0;
        h5 = 0;
        h6 = 0;
        h7 = 0;

        rh0 = 0;
        rh1 = 0;
        rh2 = 0;
        rh3 = 0;
        rh4 = 0;
        rh5 = 0;
        rh6 = 0;
        rh7 = 0;

        numSymmetry = 0;

        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){

                digit = x%2;
                x /= 2;             

                switch (i){
                    case 0:
                        h0 += digit << j;
                        
                        rj = 7 - j;
                        rh0 += digit << rj;
                        
                        break;
                    
                    case 1:
                        h1 += digit << j;
                        
                        rj = 7 - j;
                        rh1 += digit << rj;
                        
                        break;

                    case 2:
                        h2 += digit << j;
                        
                        rj = 7 - j;
                        rh2 += digit << rj;
                        
                        break;

                    case 3:
                        h3 += digit << j;
                        
                        rj = 7 - j;
                        rh3 += digit << rj;
                        
                        break;

                    case 4:
                        h4 += digit << j;
                        
                        rj = 7 - j;
                        rh4 += digit << rj;
                        
                        break;

                    case 5:
                        h5 += digit << j;
                        
                        rj = 7 - j;
                        rh5 += digit << rj;
                        
                        break;
                    
                    case 6:
                        h6 += digit << j;
                        
                        rj = 7 - j;
                        rh6 += digit << rj;
                        
                        break;
                    
                    case 7:
                        h7 += digit << j;
                        
                        rj = 7 - j;
                        rh7 += digit << rj;
                        
                        break;
                                                                                                                                                               
                }

                switch (j){
                    case 0:
                        v0 += digit << i;
                        break;
                    
                    case 1:
                        v1 += digit << i;
                        break;

                    case 2:
                        v2 += digit << i;
                        break;

                    case 3:
                        v3 += digit << i;
                        break;

                    case 4:
                        v4 += digit << i;
                        break;

                    case 5:
                        v5 += digit << i;
                        break;
                    
                    case 6:
                        v6 += digit << i;
                        break;
                    
                    case 7:
                        v7 += digit << i;
                        break;
                                                                                                                                                               
                }

            }
        }

        if (h0 == h7 && h1 == h6 && h2 == h5 && h3 == h4){
            numSymmetry += 1;
        }

        if (v0 == v7 && v1 == v6 && v2 == v5 && v3 == v4){
            numSymmetry += 1;
        }

        if (v0 == h0 && v1 == h1 && v2 == h2 && v3 == h3 && v4 == h4 && v5 == h5 && v6 == h6 && v7 == h7){
            numSymmetry += 1;
        }

        if (v7 == rh0 && v6 == rh1 && v5 == rh2 && v4 == rh3 && v3 == rh4 && v2 == rh5 && v1 == rh6 && v0 == rh7){
            numSymmetry += 1;
        }

        printf("%d ", numSymmetry);

        if (v0 == v7 && v1 == v6 && v2 == v5 && v3 == v4){
            numSymmetry += 1;
            printf("V");
        }

        if (h0 == h7 && h1 == h6 && h2 == h5 && h3 == h4){
            numSymmetry += 1;
            printf("H");
        }

        if (v0 == h0 && v1 == h1 && v2 == h2 && v3 == h3 && v4 == h4 && v5 == h5 && v6 == h6 && v7 == h7){
            numSymmetry += 1;
            printf("A");
        }

        if (v7 == rh0 && v6 == rh1 && v5 == rh2 && v4 == rh3 && v3 == rh4 && v2 == rh5 && v1 == rh6 && v0 == rh7){
            numSymmetry += 1;
            printf("B");
        }

        if (numSymmetry == 0){
            printf("-");
        }
        

        printf("\n");


    }


    return 0;
}