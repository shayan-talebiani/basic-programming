#include <stdio.h>
#include <string.h>

void set_a(int n, int a[n][n]);
void print_a(int n, int a[n][n]);

void transpose(int n, int a[n][n]);
void rotate(int n, int a[n][n]);
void swap(int n, int a[n][n]);
void saddle(int n, int a[n][n]);

int main(){

    int n;
    scanf("%d", &n);

    int a[n][n];
    set_a(n, a);

    while (1){
        
        char command[20];
        scanf(" %s", command);

        if (strcmp("end", command) == 0){
            
            print_a(n, a);
            break;
        
        }else if (strcmp("transpose", command) == 0){

            transpose(n, a);
            
        }else if(strcmp("rotate", command) == 0){

            rotate(n, a);
            
        }else if(strcmp("swap", command) == 0){

            swap(n, a);
            
        }else if(strcmp("saddle", command) == 0){

            saddle(n, a);
            
        }
        
    }
    
    return 0;
}


void set_a(int n, int a[n][n]){

    int tr_n = -1, tr_s = n, tr_w = -1, tr_e = n;
    int i = 0, j = 0;
 

    while (1){
        
        while (j + 1 < tr_e){
            scanf(" %d", &a[i][j]);
            j++;
        }

        tr_n = i;
        
        while (i + 1 < tr_s){
            scanf(" %d", &a[i][j]);
            i++;
        }

        tr_e = j;

        while (j - 1 > tr_w){
            scanf(" %d", &a[i][j]);
            j--;
        }

        tr_s = i;
        
        while (i - 1 > tr_n){
            scanf(" %d", &a[i][j]);
            i--;
        }

        tr_w = j;

        if (tr_s == tr_n && tr_e == tr_w){
            scanf(" %d", &a[i][j]);
            break;
        }
        

    }
    
    
}

void print_a(int n, int a[n][n]){
    
    for (int i = 0; i < n; i++){
        
        for (int j = 0; j < n; j++){
            printf("%d ", a[i][j]);
        }
        
        printf("\n");
    }
    
}


void transpose(int n, int a[n][n]){

    for (int i = 0; i < n; i++){
        
        for (int j = i + 1; j < n; j++){
            
            int temp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = temp;

        }

    }

}

void rotate(int n, int a[n][n]){

    char command[20]; 
    scanf(" %s", command);

    int clockwise;

    if (strcmp("clockwise", command) == 0){
        clockwise = 1;
    }else{
        clockwise = 0;
        scanf(" %s", command);
    }

    int mx;
    int my;

    if (n % 2 == 0){
        mx = n / 2 - 1;
        my = n / 2 - 1;
    }else{
        mx = n / 2;
        my = n / 2 - 1;
    }


    for (int i = 0; i <= my; i++){
        
        for (int j = 0; j <= mx; j++){
            
            int temp = a[i][j];
            
            if (clockwise){
                a[i][j] = a[n - 1 - j][i];
                a[n - 1 - j][i] = a[n - 1 - i][n - 1 - j];
                a[n - 1 - i][n - 1 - j] = a[j][n - 1 - i];
                a[j][n - 1 - i] = temp;
            }else{
                a[i][j] = a[j][n - 1 - i];
                a[j][n - 1 - i] = a[n - 1 - i][n - 1 - j];
                a[n - 1 - i][n - 1 - j] = a[n - 1 - j][i];
                a[n - 1 - j][i] = temp;
            }
            
            
        }
    }
    
    
}

void swap(int n, int a[n][n]){

    char command[20]; 
    scanf(" %s", command);

    int x, y, rows;

    if (strcmp("rows", command) == 0){
        rows = 1;
    }else{
        rows = 0;
    }

    scanf(" %d", &x);
    scanf(" %s", &command);
    scanf(" %d", &y);

    
    if (!(0 < x && x <= n) || !(0 < y && y <= n)){
        printf("invalid numbers for swapping.\n");
        return;
    }

    x--;
    y--;
    

    for (int i = 0; i < n; i++){

        if (rows){

            int temp = a[x][i];
            a[x][i] = a[y][i];
            a[y][i] = temp;
        
        }else{

            int temp = a[i][x];
            a[i][x] = a[i][y];
            a[i][y] = temp;

        }
        
        
    }
    

}

void saddle(int n, int a[n][n]){

    int min_in_row[n];
    int max_in_column[n];

    for (int i = 0; i < n; i++){

        for (int j = 0; j < n; j++){
            
            if(j == 0 || min_in_row[i] > a[i][j]){

                min_in_row[i] = a[i][j];

            }

            if(j == 0 || max_in_column[i] < a[j][i]){

                max_in_column[i] = a[j][i];

            }

        }
        
    }


    for (int i = 0; i < n; i++){

        for (int j = 0; j < n; j++){
            
            if(min_in_row[i] == a[i][j] && max_in_column[j] == a[i][j]){

                printf("(%d, %d)", i + 1, j + 1);

            }

        }
        
    }

    printf("\n");
    

}
