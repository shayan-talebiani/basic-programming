#include <stdio.h>


int calculate_state_count(int n, int selected_index[n], int index, int last_number);

void set_selected_indexes(int n, int selected_indexes[n]);
void copy_array(int n, int selected_indexes[n], int new_selected_indexes[n]);

int check_prime_number(int number);

int main(){

    int n;
    scanf("%d", &n);

    int state_count;

    int selected_indexes[n];

    set_selected_indexes(n, selected_indexes);
    state_count = calculate_state_count(n, selected_indexes, 0, 0);

    printf("%d\n", state_count);

    return 0;

}

int calculate_state_count(int n, int selected_indexes[n], int index, int last_number){

    //end

    if (index > n - 1){

        if (check_prime_number(1 + last_number) == 1){
        
            return 1;
        
        }else{
            return 0;
        }



    }
    
    //first time

    if (index == 0){

        selected_indexes[0] = 1;

        return calculate_state_count(n, selected_indexes, 1, 1);
    
    }
    

    //other times

    int state_count = 0;

    for (int i = 0; i < n; i++){

        if (selected_indexes[i] == 1){
            continue;
        }
        
        if (check_prime_number(i + 1 + last_number) == 1){        

            
            int new_selected_indexes[n];
            copy_array(n, selected_indexes, new_selected_indexes);

            new_selected_indexes[i] = 1;

            state_count += calculate_state_count(n, new_selected_indexes, index + 1, i + 1);

        }
        
    }
    
    return state_count;

}


void set_selected_indexes(int n, int selected_indexes[n]){
    
    for (int i = 0; i < n; i++){
        
        selected_indexes[i] = 0;

    }
    
}

void copy_array(int n, int selected_indexes[n], int new_selected_indexes[n]){

    for (int i = 0; i < n; i++){
        
        new_selected_indexes[i] = selected_indexes[i];

    }
    
}

int check_prime_number(int number){

    if (number == 0 && number == 1){
        return 0;
    }
    

    int i = 2;

    while (number >= i * i){
        
        if (number % i == 0 ){
            return 0;
        }

        i += 1;


    }
    


    return 1;
}
