#include <stdio.h>
#include <string.h>

void set_list_and_dictionary_word(int text_len, char decoded_text[text_len], char dictionary_words[5000][64],
                                char text2words_list[5000][64], int word_count[2]);
void set_encoded_text(char encoded_text[10000], char dictionary_words[5000][64], char text2words_list[5000][64], int word_count[2]);

int main(){

    char decoded_text[10001];
    fgets(decoded_text, sizeof(decoded_text), stdin);

    int text_len = strlen(decoded_text);

    int word_count[2]; // 0: dictionary_words word count, 1: text2words_list word count
    char dictionary_words[5000][64];
    char text2words_list[5000][64];

    set_list_and_dictionary_word(text_len, decoded_text, dictionary_words, text2words_list, word_count);

    char encoded_text[10000];
    set_encoded_text(encoded_text, dictionary_words, text2words_list, word_count);

    printf("%s", encoded_text);

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
        
        while ( (decoded_text[i] >= 'a' && decoded_text[i] <= 'z') || (decoded_text[i] >= 'A' && decoded_text[i] <= 'Z') ){
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
                    
                    strcpy(dictionary_words[word_count[0]], word);
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

void set_encoded_text(char encoded_text[10000], char dictionary_words[5000][64], char text2words_list[5000][64], int word_count[2]){

    // 0: dictionary_words word count, 1: text2words_list word count

    int dictionary_new_words[word_count[0]];
    int dictionary_new_word_count = 0;

    encoded_text[0] = '\0';

    for (int i = 0; i < word_count[0]; i++){
        dictionary_new_words[i] = -1;
    }

    for (int i = 0; i < word_count[1]; i++){


        int in_dictionary = 0;

        for (int j = 0; j < word_count[0]; j++){


            if (0 == strcmp(text2words_list[i], dictionary_words[j])){

                if (dictionary_new_words[j] == -1){
                    
                    printf("%d: %s\n", dictionary_new_word_count, dictionary_words[j]);

                    dictionary_new_words[j] = dictionary_new_word_count;
                    dictionary_new_word_count += 1;

                }

                int frequence = 0;

                while (0 == strcmp(text2words_list[i], text2words_list[i+1]) && i + 1 < word_count[1]){
                    frequence += 1;
                    i += 1;
                }
                
                if (frequence == 0){
                    char add_str[10];
                    sprintf(add_str, "%d ", dictionary_new_words[j]); 
                    strcat(encoded_text, add_str);
                }else{
                    char add_str[10];
                    sprintf(add_str, "%d[%d] ", dictionary_new_words[j], frequence + 1); 
                    strcat(encoded_text, add_str);
                }
                
                in_dictionary = 1;
                
            }
            

        }

        if (in_dictionary == 0){
            strcat(encoded_text, text2words_list[i]);
            strcat(encoded_text, " ");
        }
        

    }
    
}
