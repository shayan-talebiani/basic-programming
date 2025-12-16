#include <stdio.h>
#include <string.h>


char LOWER_LETTERS[] = "abcdefghijklmnopqrstuvwxyz";
char CAPITAL_LETTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void set_list_and_dictionary_word(int text_len, char decoded_text[text_len], char dictionary_words[5000][64],
                                char text2words_list[5000][64], int word_count[2]);


int main(){

    char decoded_text[10000];
    fgets(decoded_text, sizeof(decoded_text), stdin);

    int text_len = strlen(decoded_text);

    int word_count[2]; // 0: dictionary_words word count, 1: text2words_list word count
    char dictionary_words[5000][64];
    char text2words_list[5000][64];

    set_list_and_dictionary_word(text_len, decoded_text, dictionary_words, text2words_list, word_count);

    printf("%d %d", word_count[0], word_count[1]);

    return 0;
}

void set_list_and_dictionary_word(int text_len, char decoded_text[text_len], char dictionary_words[5000][64],
                                char text2words_list[5000][64], int word_count[2]){

    //word_count => 0: dictionary_words word count, 1: text2words_list word count

    word_count[0] = 0;
    word_count[1] = 0;

    int unique_word_count = 0;
    char unique_words[5000][64];
    int unique_words_count[5000];

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
            strcpy(text2words_list[word_count[1]], word);
            word_count[1] += 1;
        }
        
        
        int new_word = 1;

        for (int j = 0; j < unique_word_count; j++){

            if (0 == strcmp(unique_words[j],  word)){
                    
                unique_words_count[j] += 1;
                new_word = 0;

                if (unique_words_count[j] == 2){
                    
                    strcpy(dictionary_words[unique_word_count], word);
                    word_count[0] += 1;

                }
                
                
            }

        }

        if (new_word == 1){
            
            strcpy(unique_words[unique_word_count], word);

            unique_words_count[unique_word_count] = 1;
            unique_word_count += 1;

        }
        

    }

}
