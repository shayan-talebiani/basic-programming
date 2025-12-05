#include <stdio.h>

char CAPITAL_LETTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char LOWER_LETTERS[] = "abcdefghijklmnopqrstuvwxyz";
char MARKS[] = ".!,?";
char MATHEMATICAL_ELEMENTS[] = "+-/*=";
char DIGITS[] = "0123456789";


void clean_up(char text[], int size);
int validate(char text[], int size);
void decoding(char text[], int size);

int set_size(char text[], int size);

void remove_element(char text[], int size, int element_index);
void add_space(char text[], int size, int element_index);
int digit2word(char text[], int size, int element_index);
int tens_digit2word(char text[], int size, int element_index);
int teen_digit2word(char text[], int size, int element_index);
void add_zero(char text[], int size, int element_index);
int add_hundred(char text[], int size, int element_index);
void add_word2text(char text[], int size, int element_index, char new_word[], int new_word_size);

int check_capital_letter(char element);
int check_lower_letter(char element);
int check_mark(char element);
int check_mathemathical(char element);
int check_digit(char element);

int main(){

    int size;
    char text[2000];
    
    fgets(text, sizeof(text), stdin);

    size = sizeof(text);
    size = set_size(text, size);


    if(validate(text, size) == 0){
        
        printf("The message may have been leaked!");

    }else{
        
        decoding(text, size);
        size = sizeof(text);
        size = set_size(text, size);
        clean_up(text, size);

        printf("%s", text);
    }


    return 0;
}


void clean_up(char text[], int size){

    int first_element_line = 1;

    int first_letter_line = 1;
    int first_letter_sentence = 1;


    for (int i = 0; i < size; i++){
        
        if (text[i] == ' '){

            if(first_element_line == 1){
                
                remove_element(text, size, i);
        
                i -= 1;
                size -= 1;

            }else if (i < size - 1 && text[i+1] == ' '){
                
                remove_element(text, size, i);

                i -= 1;
                size -= 1;

            }
            
        }else if (check_capital_letter(text[i]) != -1){
            
            if (first_element_line == 1){
                first_element_line = 0;
            }

            if(first_letter_sentence == 1){
                
                first_letter_sentence = 0;
                first_letter_line = 0;

            }else{

                int index = check_capital_letter(text[i]);
                text[i] = LOWER_LETTERS[index];

            }

        }else if (check_lower_letter(text[i]) != -1){
            
            if (first_element_line == 1){
                first_element_line = 0;
            }

            if(first_letter_sentence == 1){
                
                first_letter_sentence = 0;
                first_letter_line = 0;

                int index = check_lower_letter(text[i]);
                text[i] = CAPITAL_LETTERS[index];

            }
        
        }else if (check_mark(text[i]) != -1){

            if (first_element_line == 1){
                first_element_line = 0;
            }
            
            if (text[i] != ','){
                first_letter_sentence = 1;
            }

            if (i > 0 && text[i-1] == ' '){
                
                remove_element(text, size, i-1);

                i -= 1;
                size -= 1;

            }
            
            if (i < size - 1 && text[i+1] != ' '){

                add_space(text, size, i + 1);

                i += 1;
                size += 1;
            }

        }else if (check_mathemathical(text[i]) != -1){
            
            if (first_element_line == 1){
                first_element_line = 0;
            }
            
            /*
            if (i > 0 && text[i-1] == ' '){
                
                if (i > 1){
                    
                    if (check_lower_letter(text[i-2]) == -1 && check_capital_letter(text[i-2]) == -1 && check_mark(text[i-2]) == -1){
                        remove_element(text, size, i-1);

                        i -= 1;
                        size -= 1;
                    }

                }else{

                    remove_element(text, size, i-1);

                    i -= 1;
                    size -= 1;
                }

            }
            
            if (i < size - 1 && text[i+1] == ' '){

                if (i < size - 2){

                    if (check_lower_letter(text[i+2]) == -1 && check_capital_letter(text[i+2]) == -1){
                        remove_element(text, size, i+1);

                        i -= 1;
                        size -= 1;
                    }

                }else{
                    remove_element(text, size, i+1);

                    i -= 1;
                    size -= 1;
                }


            }
            */

        }else if (check_digit(text[i]) != -1){
            if (first_element_line == 1){
                first_element_line = 0;
            }

        }else if(text[i] == '\0'){
            break;
        }
    
    }
    
}

int validate(char text[], int size){

    for (int i = 0; i < size; i++){

        int valid = 0;
        
        if (check_capital_letter(text[i]) != -1){
         
            valid = 1;
        }

        if (check_lower_letter(text[i]) != -1){
         
            valid = 1;
        }

        if (check_mark(text[i]) != -1){
            
            valid = 1;
        }

        if (check_mathemathical(text[i]) != -1){

            valid = 1;
        }

        if (check_digit(text[i]) != -1){

            valid = 1;
        }

        if (text[i] == ' '){

            valid = 1;
        }

        if (valid == 0){
            return 0;
        }
        

    }

    return 1;

}

void decoding(char text[], int size){
    
    for (int i = 0; i < size - 1; i++){
        
        if (check_digit(text[i]) != -1){

            //don't type

            int digit_counts = 1;

            int j = i + 1;
            
            while (check_digit(text[j]) != -1 && j < size -1){

                j += 1;
                digit_counts += 1;
            }          

            while (text[j] == ' ' && j < size -1){
                j += 1;
            }    
            
            if (check_mathemathical(text[j]) != -1 && j < size -1){
                continue;
            }
            
            j = i - 1;

            while (check_digit(text[j]) != -1 && j > -1){
                j -= 1;
            }          
            
            while (text[j] == ' ' && j > -1){
                j -= 1;
            }  

            if (check_mathemathical(text[j]) != -1 && j > -1){
                continue;
            }

            //type

            j = i;

            int start_type = 0;

            if (digit_counts == 3){
                
                digit_counts -= 1;
                
                if (text[j] != '0'){

                    if (j>0 && text[j-1] != ' '){
                        add_space(text, size, j);
                        j += 1;
                        size += 1;
                        i = j;
                    }
                    
                    
                    start_type = 1;

                    j = digit2word(text, size, j);
                    size += j - i;
                    
                    add_space(text, size, j + 1);
                    j += 1;
                    size += 1;

                    add_space(text, size, j + 1);
                    j += 1;
                    size += 1;

                    int k = j;

                    j = add_hundred(text, size, j);
                    size += j- k;

                    add_space(text, size, j + 1);
                    j += 2;
                    size += 1;

                    i = j;
                }else{

                    remove_element(text, size, j);
                    size -= 1;
                }

            }

            int finish_type = 0;

            if (digit_counts == 2){

                digit_counts -= 1;
                
                if (text[j] != '0' && (text[j] != '1' || text[j + 1] == '0')){

                    if (j>0 && text[j-1] != ' '  && start_type == 0){
                        add_space(text, size, j);
                        j += 1;
                        size += 1;
                        i = j;
                    }

                    start_type = 1;
                    
                    j = tens_digit2word(text, size, j);
                    size += j - i;
                    
                    add_space(text, size, j + 1);
                    j += 2;
                    size += 1;

                    i = j;
                }else if(text[j] == '1' && text[j + 1] != '0'){

                    if (j>0 && text[j-1] != ' ' && start_type == 0){
                        add_space(text, size, j);
                        j += 1;
                        size += 1;
                        i = j;
                    }

                    start_type = 1;
                    finish_type = 1;

                    j = teen_digit2word(text, size, j);
                    size += j - i;

                    j += 1;

                    remove_element(text, size, j);
                    size -= 1;
                    
                    if (text[j] != ' ' && j < size){
                        add_space(text, size, j);
                        size += 1;
                    }
                    
                    i = j;

                }else{

                    remove_element(text, size, j);
                    size -= 1;
                    
                }
            }
            
            if (digit_counts == 1 && finish_type == 0){

                if (text[j] != '0'){

                    if (j>0 && text[j-1] != ' ' && start_type == 0){
                        add_space(text, size, j);
                        j += 1;
                        size += 1;
                        i = j;
                        
                    }
                    
                    j = digit2word(text, size, j);
                    size += j - i;

                    j += 1;

                    if (text[j] != ' ' && j < size){
                        add_space(text, size, j);
                        size += 1;
                    }

                    i = j;
                }else if(start_type == 0){

                    if (j>0 && text[j-1] != ' '){
                        add_space(text, size, j);
                        j += 1;
                        size += 1;
                        i = j;
                    }

                    add_zero(text, size, j);
                    j += 4;
                    size += 3;

                    if (text[j] != ' ' && j < size){
                        add_space(text, size, j);
                        size += 1;
                    }
                    
                    i = j;

                }else{
                    
                    remove_element(text, size, j);
                    size -= 1;

                    if (text[j] == ' '){
                        remove_element(text, size, j);
                        size -= 1;
                        j -= 1;
                        i = j;
                    }
                    

                }

            }

        }
        
    }
}


int set_size(char text[], int size){

    for (int i = 0; i < size; i++){

        if(text[i] == '\n'){

            text[i] = '\0';

            i += 1;

            return i;
            
        }

        if(text[i] == '\0'){

            i += 1;

            return i;
        }

    }

}


void remove_element(char text[], int size, int element_index){
    
    for (int i = element_index; i < size; i++){
        
        text[i] = text[i + 1];

        if(text[i] == '\0'){
            break;
        }

    }
}

void add_space(char text[], int size, int element_index){
    
    for (int i = size + 1; i > element_index; i--){

        text[i] = text[i - 1];

    }

    text[element_index] = ' ';
}

int digit2word(char text[], int size, int element_index){

    switch (text[element_index]){
        case '1':{
            char new_word[] = "one";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '2':{
            char new_word[] = "two";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '3':{
            char new_word[] = "three";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '4':{
            char new_word[] = "four";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '5':{
            char new_word[] = "five";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '6':{
            char new_word[] = "six";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '7':{
            char new_word[] = "seven";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '8':{
            char new_word[] = "eight";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '9':{
            char new_word[] = "nine";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
    }
}

int tens_digit2word(char text[], int size, int element_index){
    switch (text[element_index]){
        case '1':{
            char new_word[] = "ten";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '2':{
            char new_word[] = "twenty";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '3':{
            char new_word[] = "thirty";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '4':{
            char new_word[] = "forty";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '5':{
            char new_word[] = "fifty";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '6':{
            char new_word[] = "sixty";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '7':{
            char new_word[] = "seventy";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '8':{
            char new_word[] = "eighty";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '9':{
            char new_word[] = "ninety";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
    }
}

int teen_digit2word(char text[], int size, int element_index){
        switch (text[element_index + 1]){
        case '1':{
            char new_word[] = "eleven";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '2':{
            char new_word[] = "twelve";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '3':{
            char new_word[] = "thirteen";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '4':{
            char new_word[] = "fourteen";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '5':{
            char new_word[] = "fifteen";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '6':{
            char new_word[] = "sixteen";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '7':{
            char new_word[] = "seventeen";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '8':{
            char new_word[] = "eighteen";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
        case '9':{
            char new_word[] = "nineteen";
            int new_word_size = sizeof(new_word) - 1;
            add_word2text(text, size, element_index, new_word, new_word_size);
            return (new_word_size + element_index - 1);
        }
    }
}

void add_zero(char text[], int size, int element_index){
    char new_word[] = "zero";
    int new_word_size = sizeof(new_word) - 1;
    add_word2text(text, size, element_index, new_word, new_word_size);
}

int add_hundred(char text[], int size, int element_index){
    char new_word[] = "hundred";
    int new_word_size = sizeof(new_word) - 1;
    add_word2text(text, size, element_index, new_word, new_word_size);
    return (element_index + 6);
}

void add_word2text(char text[], int size, int element_index, char new_word[], int new_word_size){
    
    for (int i = 0; i < new_word_size ; i++){
        text[element_index + i] = new_word[i];


        if (i < new_word_size - 1){
            add_space(text, size, element_index + i + 1);
        }
        
        if (i > 0){
            size += 1;
        }
        
    }

    
}


int check_capital_letter(char element){
    
    int size = sizeof(CAPITAL_LETTERS);
    
    for (int i = 0; i < size; i++){
        
        if (CAPITAL_LETTERS[i] == element){
            return i;
        }
        
    }

    return -1;
    
}

int check_lower_letter(char element){
    
    int size = sizeof(LOWER_LETTERS);
    
    for (int i = 0; i < size; i++){
        
        if (LOWER_LETTERS[i] == element){
            return i;
        }
        
    }

    return -1;

}

int check_mark(char element){

    int size = sizeof(MARKS);
    
    for (int i = 0; i < size; i++){
        
        if (MARKS[i] == element){
            return 1;
        }
        
    }

    return -1;

}

int check_mathemathical(char element){

    int size = sizeof(MATHEMATICAL_ELEMENTS);
    
    for (int i = 0; i < size; i++){
        
        if (MATHEMATICAL_ELEMENTS[i] == element){
            return 1;
        }
        
    }

    return -1;

}

int check_digit(char element){

    int size = sizeof(DIGITS);
    
    for (int i = 0; i < size; i++){
        
        if (DIGITS[i] == element){
            return i;
        }
        
    }

    return -1;

}
