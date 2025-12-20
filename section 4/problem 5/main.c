#include <stdio.h>
#include <string.h>


int move(int text_len, int location, int n);
int remove_enter(int len, char text[len + 1]);


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

        }else if (strcmp("rooting", command) == 0){
            
        }else if (strcmp("add", command) == 0){
            
            char word[501];
            scanf(" %s", word);
        
        }else if (strcmp("reverse", command) == 0){
            
        }else if (strcmp("WOW", command) == 0){
            
        }else if (strcmp("lower", command) == 0){
            
        }else if (strcmp("upper", command) == 0){
            
        }else if (strcmp("change", command) == 0){
            
            int amount;
            scanf(" %d", &amount);

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

int remove_enter(int len, char text[len + 1]){

    if (text[len - 1] == '\n'){
        text[len - 1] = '\0';
        return (len -1);
    }

    return len;
}