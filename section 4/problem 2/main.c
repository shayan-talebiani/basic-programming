#include <stdio.h>

int set_text_len(int text_len, char encoded_text[text_len]);

int find_e(int text_len, char encoded_text[text_len], char lower_letters[27], char capital_letters[27]);
void set_letters_count(double letters_count[26]);
void set_decoded_text(int text_len, char encoded_text[text_len], char decoded_text[text_len],
                    int shift_number, char lower_letters[27], char capital_letters[27]);

                    
int main(){

    char lower_letters[] = "abcdefghijklmnopqrstuvwxyz";
    char capital_letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    char encoded_text[501];
    fgets(encoded_text, sizeof(encoded_text), stdin);

    int text_len = sizeof(encoded_text);//printf("%d\n", text_len);
    text_len = set_text_len(text_len, encoded_text);//printf("%d\n", text_len);

    int encoded_e_index = find_e(text_len, encoded_text, lower_letters, capital_letters);

    if (encoded_e_index != -1){
        
        int shift_number;

        if (encoded_e_index < 4){

            encoded_e_index += 26;
        
        }

        shift_number = encoded_e_index - 4;

        printf("%d\n", shift_number);
        
        char decoded_text[text_len];
        set_decoded_text(text_len, encoded_text, decoded_text, shift_number, lower_letters, capital_letters);

    }
    

    return 0;
}



int set_text_len(int text_len, char encoded_text[text_len]){
    
    for (int i = 0; i < text_len; i++){
    
        if (encoded_text[i] == '\0'){

            return i + 1;

        }
        
    }
}


int find_e(int text_len, char encoded_text[text_len], char lower_letters[27], char capital_letters[27]){

    double letter_count = 0;
    double letters_count[26];

    set_letters_count(letters_count);

    for (int i = 0; i < text_len; i++){
        
        for (int j = 0; j < 26; j++){
        
            if (encoded_text[i] == lower_letters[j] || encoded_text[i] == capital_letters[j]){
                letter_count += 1;
                letters_count[j] += 1;
            }
            
        }
        
    }

    double max_frequence = 0;
    int max_frequence_index;
    
    for (int i = 0; i < 26; i++){
    
        if (letters_count[i] > max_frequence){

            max_frequence = letters_count[i];
            max_frequence_index = i;

        }
        
    }

    max_frequence /= letter_count;
    max_frequence *= 100;
    //printf("%d", max_frequence);
    if (max_frequence <= (double)14 && max_frequence >= (double)10){
        
        return max_frequence_index;
    
    }else{

        printf("Ciphertext is either too short or not a Caesar cipher!");
        return -1;

    }
}

void set_letters_count(double letters_count[26]){

    for (int i = 0; i < 26; i++){
        letters_count[i] = 0;
    }
    
}

void set_decoded_text(int text_len, char encoded_text[text_len], char decoded_text[text_len],
                    int shift_number, char lower_letters[27], char capital_letters[27]){


    for (int i = 0; i < text_len; i++){

        int letter = 0;

        for (int j = 0; j < 26; j++){
            
            if (encoded_text[i] == lower_letters[j]){
                
                letter = 1;

                int new_j = j;

                if (j < shift_number){
                    new_j += 26;
                }
                
                int new_index = (new_j - shift_number) % 26;
                decoded_text[i] = lower_letters[new_index];

            }else if (encoded_text[i] == capital_letters[j]){

                letter = 1;

                int new_j = j;

                if (j < shift_number){
                    new_j += 26;
                }

                int new_index = (new_j - shift_number) % 26;
                decoded_text[i] = capital_letters[new_index];

            }
            
        }

        if (letter == 0){

            decoded_text[i] = encoded_text[i];
        
        }
        

    }
    
    printf("%s", decoded_text);

}
