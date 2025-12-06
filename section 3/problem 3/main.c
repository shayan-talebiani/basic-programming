#include <stdio.h>

void set_x(int n, int x[n]);

int bmm(int a, int b);
int kmm(int a, int b);

int calculate(int n, char text[2 * n], int x[n]);

int x_index = 0;
int text_index = 0;

int main(){

    int n;

    scanf("%d", &n);

    char text[2 * n];

    scanf("%s", &text);

    int x[n];

    set_x(n, x);

    int number = calculate(n, text, x);
    printf("%d", number);


    return 0;


}


void set_x(int n, int x[n]){

    for (int i = 0; i < n; i++){
        
        int element;

        scanf("%d", &element);

        x[i] = element;
    }


}


int bmm(int a, int b)
{

    if (a < b){

        int a_copy = a;
        a = b;
        b = a_copy;
        
    }
    
    while  (b != 0){
        int r = a % b ;
        a = b;
        b = r; 
    }

    return a;
}

int kmm(int a, int b){

    return ((a * b) / bmm(a, b));

}

int calculate(int n, char text[2 * n], int x[n]){


    if (text[text_index] == '&'){

        int a;
        int b;

        text_index += 1;        

        a = calculate(n, text, x);
        b = calculate(n, text, x);

        return bmm(a, b);

    }else if (text[text_index] == '@'){

        int a;
        int b;

        text_index += 1;

        a = calculate(n, text, x);
        b = calculate(n, text, x);

        return kmm(a, b);        

    }else if (text[text_index] == 'X'){

        text_index += 1;
        x_index += 1;

        return x[x_index - 1];

    }
    

    

}
