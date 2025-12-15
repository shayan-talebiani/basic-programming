#include <stdio.h>
#include <string.h>

int main(){

    char lower_letters[] = "abcdefghijklmnopqrstuvwxyz";
    char capital_letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    char decoded_text[501];
    fgets(decoded_text, sizeof(decoded_text), stdin);

    int text_len = strlen(decoded_text);



    return 0;
}


int set_text_len(int text_len, char encoded_text[text_len]){
    
    for (int i = 0; i < text_len; i++){
    
        if (encoded_text[i] == '\0'){

            return i + 1;

        }
        
    }
}
