#include <stdio.h>

void get_a(int n, int a[n][n]);

int get_group_count(int n, int k, int a[n][n]);

int calculate_group_count(int n, int k, int a[n][n], int index, int chosen_element_count, int last_chosen_element, int sum);

int main(){

    int n;
    int k;

    int group_count;

    scanf("%d %d", &n, &k);

    int a[n][n];

    get_a(n, a);

    group_count = get_group_count(n, k, a);

    printf("%d", group_count);

    return 0;
}

void get_a(int n, int a[n][n]){

    for (int i = 0; i < n; i++){

        for (int j = 0; j < n; j++){

            int familiar;

            scanf("%d", &familiar);

            a[i][j] = familiar;


        }

    }

}


int get_group_count(int n, int k, int a[n][n]){

    int group_count;


    int sum = 0;
    int index = 0;
    int chosen_element_count = 0;
    int last_chosen_element = -1;

    group_count = calculate_group_count(n, k, a, index, chosen_element_count, last_chosen_element, sum);

    return group_count;

}


int calculate_group_count(int n, int k, int a[n][n], int index, int chosen_element_count, int last_chosen_element, int sum){

    int group_count = 0;

    //end

    if ( (sum  + (k - chosen_element_count)) * 2 < (k - 1)){
        return 0;
    }

    if (chosen_element_count == k){

        if(sum * 2 >= (k-1) ){
            return 1;
        }else{
            return 0;
        }
    }
    
    if ( (index + (k - chosen_element_count)) == n + 1 ){
        return 0;
    }
    
    //choose

    int new_sum = sum;
    int new_last_chosen_element;

    if(last_chosen_element != -1){
        new_sum += a[last_chosen_element][index];
    }

    new_last_chosen_element = index;


    group_count += calculate_group_count(n, k, a, index + 1, chosen_element_count + 1, new_last_chosen_element, new_sum);


    //don't choose

    group_count += calculate_group_count(n, k, a, index + 1, chosen_element_count, last_chosen_element, sum);

    return group_count;

}


