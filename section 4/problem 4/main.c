#include <stdio.h>

void set_a(int n, int a[n][n]);

int calculate_state_count(int n, int a[n][n]);
void set_using_state(int n, int a[n][n], int using_state[n], int index);

int main(){

    int n;
    scanf("%d", &n);

    int a[n][n];
    set_a(n, a);

    int state_count = calculate_state_count(n, a);

    printf("%d", state_count);

    return 0;
}


void set_a(int n, int a[n][n]){

    for (int i = 0; i < n; i++){
        
        for (int j = 0; j < n; j++){
            
            int conections;
            scanf("%d", &conections);

            a[i][j] = conections;

        }
    
    }
    

}

int calculate_state_count(int n, int a[n][n]){

    int using_state[n];
    int state_count = 0;

    for (int i = 0; i < n; i++){
        using_state[i] = 0;
    }

    for (int i = 0; i < n; i++){

        if (using_state[i] == 0){
            
            state_count += 1;

            using_state[i] = 1;

            set_using_state(n, a, using_state, i);

        }
        
    }
    

    return state_count;
}

void set_using_state(int n, int a[n][n], int using_state[n], int index){
    
    for (int i = 0; i < n; i++){

        if (using_state[i] == 0 && a[index][i] > 0){

            using_state[i] = 1;

            set_using_state(n, a, using_state, i);

        }
        
    }

}
