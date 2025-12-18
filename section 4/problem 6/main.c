#include <stdio.h>
#include <string.h>

int set_winner_num(int r, int l, int text_len, char text[text_len+1], int cheking_matrix[text_len][text_len], int winner_matrix[text_len][text_len]);

int check_text(int r, int l, int text_len, char text[text_len+1], int cheking_matrix[text_len][text_len]);

void set_matrix(int text_len, int cheking_matrix[text_len][text_len], int winner_matrix[text_len][text_len]);

int main(){
    
    int t;
    scanf("%d", &t);
    getchar();

    for (int i = 0; i < t; i++){

        char text[501];
        fgets(text, sizeof(text), stdin);
        
        int text_len = strlen(text);

        if (text[text_len - 1] == '\n'){

            text[text_len - 1] = '\0';
            text_len -= 1;

        }


        int cheking_matrix[text_len][text_len]; //0: r, 1:l
        int winner_matrix[text_len][text_len]; //0: r, 1:l

        set_matrix(text_len, cheking_matrix, winner_matrix);

        if (check_text(0, 0, text_len, text, cheking_matrix) == 1){
            printf("First\n");
        }else{
            
            int winner_num = set_winner_num(0, 0, text_len, text , cheking_matrix, winner_matrix);
            
            if (winner_num == 1){
                printf("First\n");
            }else{
                printf("Second\n");
            }

        }
        
    }
    

    return 0;
}
 

int set_winner_num(int r, int l, int text_len, char text[text_len+1], int cheking_matrix[text_len][text_len], int winner_matrix[text_len][text_len]){
    
    if (winner_matrix[r][l] != -1){
        return winner_matrix[r][l];
    }

    int first_is_winner;
    int new_r, new_l;
    int new_new_r, new_new_l;

    //first player remove first word

    new_r = 1 + r;

    if (check_text(new_r, l, text_len, text, cheking_matrix) == 1){
        winner_matrix[r][l] = 1;
        return 1;
    }else{

        //second player remove first word

        new_new_r = 1 + new_r;

        if (check_text(new_new_r, l, text_len, text, cheking_matrix) == 1){
            first_is_winner = 0;
        }else{
            first_is_winner = set_winner_num(new_new_r, l, text_len, text, cheking_matrix, winner_matrix);
        }

        //second player remove last word

        if (first_is_winner == 1){

            new_new_l = 1 + l; 

            if (check_text(new_r, new_new_l, text_len, text, cheking_matrix) == 1){
                first_is_winner = 0;
            }else{
                first_is_winner = set_winner_num(new_r, new_new_l, text_len, text, cheking_matrix, winner_matrix);
            }
            

        }

    }
    
    if (first_is_winner == 1){
        winner_matrix[r][l] = 1;
        return 1;
    }
    
    //first player remove last word
    
    new_l = 1 + l;

    if (check_text(r, new_l, text_len, text, cheking_matrix) == 1){
        winner_matrix[r][l] = 1;
        return 1;
    }else{

        //second player remove first word

        new_new_r = 1 + r;

        if (check_text(new_new_r, new_l, text_len, text, cheking_matrix) == 1){
            first_is_winner = 0;
        }else{
            first_is_winner = set_winner_num(new_new_r, new_l, text_len, text, cheking_matrix, winner_matrix);
        }

        //second player remove last word

        if (first_is_winner == 1){

            new_new_l = 1 + new_l; 

            if (check_text(r, new_new_l, text_len, text, cheking_matrix) == 1){
                first_is_winner = 0;
            }else{
                first_is_winner = set_winner_num(r, new_new_l, text_len, text, cheking_matrix, winner_matrix);
            }
            

        }

    }
    
    winner_matrix[r][l] = first_is_winner;
    return first_is_winner;

}


int check_text(int r, int l, int text_len, char text[text_len+1], int cheking_matrix[text_len][text_len]){

    if (cheking_matrix[r][l] != -1){
        return cheking_matrix[r][l];
    }
    

    int new_text_len = text_len - r - l;

    if (new_text_len % 2 == 0){
        
        int limit = new_text_len/2;

        for (int i = r; i < new_text_len + r; i++){
            
            if (text[i] != text[-(i-r) + new_text_len + r -1]){
                cheking_matrix[r][l] = 0;
                return 0;
            }
            
        }

        cheking_matrix[r][l] = 1;
        return 1;
        

    }else if (new_text_len % 2 == 1){

        int limit = (new_text_len - 1)/2;

        for (int i = r; i < new_text_len + r; i++){
            
            if (text[i] != text[-(i-r) + new_text_len + r -1]){
                cheking_matrix[r][l] = 0;
                return 0;
            }
            
        }

        cheking_matrix[r][l] = 1;
        return 1;

    }
    
    cheking_matrix[r][l] = 0;
    return 0;
}

void set_matrix(int text_len, int cheking_matrix[text_len][text_len], int winner_matrix[text_len][text_len]){

    for (int i = 0; i < text_len; i++){

        for (int j = 0; j < text_len; j++){
            
            cheking_matrix[i][j] = -1;
            winner_matrix[i][j] = -1;
            
        }
    
    }
    

}
