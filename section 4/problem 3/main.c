#include <stdio.h>
#include <string.h>


char LOWER_LETTERS[] = "abcdefghijklmnopqrstuvwxyz";
char CAPITAL_LETTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int set_unique_words_count(int text_len, char decoded_text[text_len], char unique_words[5000][64], int unique_words_count[5000]);


int main(){

    char decoded_text[10000];
    fgets(decoded_text, sizeof(decoded_text), stdin);

    int text_len = strlen(decoded_text);


    int unique_word_count;
    char unique_words[5000][64];
    int unique_words_count[5000];

    unique_word_count = set_unique_words_count(text_len, decoded_text, unique_words, unique_words_count);

    printf("%d", unique_word_count);

    return 0;
}

int set_unique_words_count(int text_len, char decoded_text[text_len], char unique_words[5000][64], int unique_words_count[5000]){

    int unique_word_count = 0;

    for (int i = 0; i < text_len; i++){
        
        char word[64];

        int word_i = 0;
        
        while (strchr(LOWER_LETTERS, decoded_text[i]) != NULL || strchr(CAPITAL_LETTERS, decoded_text[i]) != NULL){
            word[word_i] = decoded_text[i];
            i += 1;
            word_i += 1;
        }

        if (word_i == 0){
            continue;
        }else{
            word[word_i] = '\0';
        }
        
        
        int new_word = 1;

        for (int j = 0; j < unique_word_count; j++){

            if (word_i == strlen(unique_words[j])){

                int different_word = 0;
                
                for (int k = 0; k < word_i + 1; k++){
                    
                    if (word[k] != unique_words[j][k]){
                        different_word = 1;
                    }
                    
                }

                if (different_word == 0){
                    
                    unique_words_count[j] += 1;
                    new_word = 0;
                
                }
                
                

            }else{
                continue;
            }
            

        }

        if (new_word == 1){
            
            strcpy(unique_words[unique_word_count], word);
            unique_word_count += 1;
            unique_words_count[i] = 1;

        }
        

    }
    

    return unique_word_count;

}
