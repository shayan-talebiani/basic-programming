#include <stdio.h>


unsigned long long set_k(int n);

int cheak_state(unsigned long long k, int n, int i, int j, int state);

unsigned long long not_element(unsigned long long k, int n, int i, int j);
int give_element(unsigned long long k, int n, int i, int j);



int main(){

    int n;

    scanf("%d", &n);

    unsigned long long k;

    k = set_k(n);

    int i = 0;
    int j = 0;

    int state = 0;

    if(0 == cheak_state(k, n, i, j, state)){
        printf("Micheal can't escape today, he has at most 26 days left!");
    }

    return 0;
}


unsigned long long set_k(int n){

    unsigned long long k = 0;

    for (int i = 0; i < n; i++){

        for (int j = 0; j < n; j++){
            

            char element;

            scanf(" %c", &element);

            unsigned long long active = 0;

            if (element == '+' || element == '#' || element == '*'){
                active = 1;
            }
            

            k += active << (i * n + j);

        }
        
    }
    
    return k;
    
}

unsigned long long not_element(unsigned long long k, int n, int i, int j){

    if (give_element(k, n, i, j) == 1){
        k -= (unsigned long long)1 << (i * n + j);
    }else{
        k += (unsigned long long)1 << (i * n + j);
    }

    return k;
    

}

int give_element(unsigned long long k, int n, int i, int j){
    return ((k >> (i * n + j)) & 1);
}

int cheak_state(unsigned long long k, int n, int i, int j, int state){

    //end

    if ( (0 < i && 0 < j) || 1 < i ){

        int pre_i, pre_j;

        if (0 < j){
            pre_i = i;
            pre_j = -1 + j;
        }else{
            pre_i = -1 + i;
            pre_j = n - 1;
        }

        if (give_element(k, n, pre_i - 1, pre_j) == 1){

            return 0;
        }

    }
    

    if (k == (unsigned long long)0){
        printf("Finally, Micheal can escape from Iran :)");
        return 1;
    }

    if (k != (unsigned long long)0 && i == n && j == 0){
        return 0;
    }

    
    //move

    int new_i, new_j;
    unsigned long long new_k;

    if (j < n - 1){
        new_i = i;
        new_j = 1 + j;
    }else{
        new_j = 0;
        new_i = 1 + i;
    }
    



    //change

    if (state == 0){

        new_k = not_element(k, n, i, j);

        if ( 0 < i){
            new_k = not_element(new_k, n, i - 1, j);
        }
        if ( 0 < j){
            new_k = not_element(new_k, n, i, j - 1);
        }        
        if ( i < n - 1){
            new_k = not_element(new_k, n, i + 1, j);
        }
        if ( j < n - 1){
            new_k = not_element(new_k, n, i, j + 1);
        }

        state = cheak_state(new_k, n, new_i, new_j, state);
    
    }else {
        return 1;
    }

    //don't change

    if (state == 0){

        state = cheak_state(k, n, new_i, new_j, state);

    } else{
        return 1;
    }

    return state;


}

