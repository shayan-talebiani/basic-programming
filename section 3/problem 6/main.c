#include <stdio.h>

void set_a(int n, int a[n][n]);

int first_check_a(int n, int a[n][n]);

int check_ij_in_a(int n, int a[n][n], int i, int j);

void copy_a(int n, int a[n][n], int new_a[n][n]);

void print_a(int n, int a[n][n]);


int fill_a(int n, int a[n][n], int i, int j);


int main(){
    
    int n;
    scanf("%d", &n);

    int a[n][n];
    set_a(n, a);
    
    if (first_check_a(n, a) == 0){

        printf("Escape is impossible!!");
    
    }else{

        int done_filling; 
        done_filling = fill_a(n, a, 0, 0);

        if (done_filling == 0){
        
            printf("Escape is impossible!!");

        }

    }
    
    return 0;
}


int fill_a(int n, int a[n][n], int i, int j){
    
    //end
    if (i != 0 || j != 0){

        int last_i, last_j;
        
        if (j > 0){
            last_i = i;
            last_j = j - 1;
        }else{
            last_i = i - 1;
            last_j = n - 1;
        }

        if (check_ij_in_a(n, a, last_i, last_j) == 1){
            
            if (last_i == n - 1 && last_j == n - 1){
                
                print_a(n, a);

                return 1;
            }
            
        }else{
            return 0;
        }
        
        
    }
    

    //each time

    int state = 0;  

    if (a[i][j] != 0){
        
        if (j + 1 < n){
            
            if (state == 0){

                state = fill_a(n, a, i, j + 1);
                
            }
            
        }else{

            if (state == 0){

                state = fill_a(n, a, i + 1, 0);
                
            }
        }

    }else{

        for (int k = 1; k <= n; k++){

            if (state == 0){

                int new_a[n][n];
                copy_a(n, a, new_a);

                new_a[i][j] = k;
                
                if (j + 1 < n){
                
                    state = fill_a(n, new_a, i, j + 1);
                
                }else if(state == 0){

                    state = fill_a(n, new_a, i + 1, 0);
                
                }
                
            }

        }



    }
    

    return state;
}



void set_a(int n, int a[n][n]){

    for (int i = 0; i < n; i++){
    
        for (int j = 0; j < n; j++){


            int element;

            scanf("%d", &element);
            a[i][j] = element;

        }
    
    }
    

}

int first_check_a(int n, int a[n][n]){

    for (int i = 0; i < n; i++){
        
        for (int j = 0; j < n; j++){
           
            if (a[i][j] != 0){

                if (check_ij_in_a(n, a, i, j) == 0){
                    
                    return 0;

                }

            }    

        }

    }

    return 1;
    
    

}

int check_ij_in_a(int n, int a[n][n], int i, int j){

    for (int index = 0; index < n; index++){
    
        if (a[i][j] == a[i][index] && j != index){
            
            return 0;

        }
        
    }
    

    for (int index = 0; index < n; index++){
    
        if (a[i][j] == a[index][j] && i != index){
            
            return 0;

        }
        
    }

    return 1;

}


void copy_a(int n, int a[n][n], int new_a[n][n]){
    
    for (int i = 0; i < n; i++){
        
        for (int j = 0; j < n; j++){

            new_a[i][j] = a[i][j]; 
        
        }
    
    }
    
}

void print_a(int n, int a[n][n]){

    for (int i = 0; i < n; i++){
        
        for (int j = 0; j < n; j++){

            if(j == 0){
            
                printf("%d", a[i][j]); 
            
            }else{

                printf(" %d", a[i][j]);

            }

        }
    
        printf("\n");

    }
}
