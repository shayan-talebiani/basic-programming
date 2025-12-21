#include <stdio.h>
#include <string.h>


int move(int text_len, int location, int n);
void add_word(int text_len, char text[501], int word_len, char word[501], int location);
int reverse(int text_len, char text[501], int location);
void lower(int text_len, char text[501], int location);
void upper(int text_len, char text[501], int location);
int change(int text_len, char text[501], int location, int amount);
void wow(int text_len, char text[501]);


void insert_space(int text_len, char text[501], int index, int adding_len);
void remove_space(int text_len, char text[501], int index, int removing_len);

int check_aeuio(char letter);
int is_letter(char a);
int remove_enter(int len, char text[501]);


int main(){

    int location = 0;

    char text[501];
    fgets(text, sizeof(text), stdin);

    int text_len = strlen(text);

    text_len = remove_enter(text_len, text);

    while (1){

        char command[20];
        scanf(" %s", command);

        if (strcmp("###", command) == 0){
            
            printf("%s\n", text);
            break;

        }else if (strcmp("location", command) == 0){
            
            printf("%d\n", location);
        
        }else if (strcmp("move", command) == 0){
            
            int n;
            scanf(" %d", &n);
            
            location = move(text_len, location, n);

        }else if (strcmp("add", command) == 0){
            
            char word[501];
            scanf(" %s", word);

            add_word(text_len, text, strlen(word), word, location);
            text_len = strlen(text);
        
        }else if (strcmp("reverse", command) == 0){
            
            location = reverse(text_len, text, location);
            
        }else if (strcmp("lower", command) == 0){

            lower(text_len, text, location);
            
        }else if (strcmp("upper", command) == 0){

            upper(text_len, text, location);
            
        }else if (strcmp("change", command) == 0){
            
            int amount;
            scanf(" %d", &amount);

            location = change(text_len, text, location, amount);

        }else if (strcmp("WOW", command) == 0){
            wow(text_len, text);
            text_len = strlen(text);
        }else if (strcmp("rooting", command) == 0){
            
        }
        
    }
    
    return 0;
}


int move(int text_len, int location, int n){

    int new_location = location + n; 

    if (text_len > new_location && new_location > -1){
        
        return new_location;

    }

    printf("Not enough characters.\n");
    
    return location;
}

void add_word(int text_len, char text[501], int word_len, char word[501], int location){

    int insert_len = word_len;

    int index = 0;

    while (is_letter(text[location + index])){
        
        index += 1;


    }

    
    int first_space = 0;
    int last_space = 0;

    int start_index = location + index;

    if (text[start_index] == '\0'){

        first_space = 1;
        last_space = 0;
        insert_len += 1;

        insert_space(text_len, text, start_index - 1, insert_len);

    }else{

        if (index == 0){

            first_space = 0;

            if (is_letter(text[start_index + 1])){
            
                last_space = 1;
                insert_len += 1;

            }

            insert_space(text_len, text, start_index, insert_len);

        }else{

            first_space = 1;
            insert_len += 1;

            insert_space(text_len, text, start_index - 1, insert_len);
        }

        
    }
    
    
    for (int i = 0; i < insert_len - first_space - last_space; i++){
        text[i + start_index + 1] = word[i];
    }

    if (first_space == 1){
        text[start_index] = ' '; 
    }

    if (last_space == 1){
        text[start_index + insert_len] = ' '; 
    }

}

int reverse(int text_len, char text[501], int location){


    if (is_letter(text[location]) == 0){
        return location;
    }
    

    int start = location;
    int word_len = -1;

    int index = 0;

    while (is_letter(text[location + index])){
        word_len += 1;
        index += 1;
    }

    index = 0;
    
    while (is_letter(text[location + index])){
        word_len += 1;
        index -= 1;
        
        if (location + index > -1){
            break;
        }
    }

    int first_letter = location + index + 1;

    int half_len = word_len / 2;
    int limit = first_letter + half_len;

    for (int i = first_letter; i < limit; i++){
        
        char temp = text[i];
        int j = first_letter + word_len - 1 - (i - first_letter);
        text[i] = text[j];
        text[j] = temp;

    }
    
    return (first_letter + word_len - 1 - (location - first_letter));
}

void lower(int text_len, char text[501], int location){

    int index = 0;

    while (is_letter(text[location + index])){

        if ('A' <= text[location + index] && 'Z' >= text[location + index]){
            text[location + index] += 32;
        }
        

        index += 1;
    }

}

void upper(int text_len, char text[501], int location){

    int index = 0;

    while (is_letter(text[location + index])){

        if ('a' <= text[location + index] && 'z' >= text[location + index]){
            text[location + index] -= 32;
        }
        

        index += 1;
    }

}

int change(int text_len, char text[501], int location, int amount){

    if (text_len - 1 < location + amount){
        
        printf("Not enough characters.");
        return location;

    }

    for (int i = location; i < location + amount; i++){
        
        if (is_letter(text[i])){
            
            if (text[i] == 'z'){
                text[i] = 'a'; 
            }else if (text[i] == 'Z'){
                text[i] = 'A';
            }else{
                text[i] += 1;
            }
            
        }
        

    }
    
    
    return (location + amount);
}

void wow(int text_len, char text[501]){
    
    for (int i = 0; i < text_len; i++){
        
        int word_index = 0;
        int aeuio = 0;

        while (is_letter(text[i + word_index])){

            if (check_aeuio(text[i + word_index])){
                aeuio += 1;
            }
        

            word_index += 1;
        }

        if (word_index - 1 >= 4 && 1 < aeuio){
            insert_space(text_len, text, i + word_index - 1, 1);
            text_len += 1;
            text[i + word_index] = '!';
            i += word_index - 1;
        }else{
            i += word_index;
        }
        
    }
    
}


void insert_space(int text_len, char text[501], int index, int adding_len){

    for (int i = text_len + 1; i > index; i--){
        text[i + adding_len] = text[i];
    }
    

}

void remove_space(int text_len, char text[501], int index, int removing_len){

    for (int i = index + 1; i < text_len + 1; i++){
        text[i] = text[i + removing_len];
    }
}


int check_aeuio(char letter){

    if (letter == 'a' || letter == 'e' || letter == 'u' || letter == 'i' || letter == 'o'){
        return 1;
    }
    
    return 0;
}

int is_letter(char a){
    return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z');
}

int remove_enter(int len, char text[501]){

    if (text[len - 1] == '\n'){
        text[len - 1] = '\0';
        return (len -1);
    }

    return len;
}