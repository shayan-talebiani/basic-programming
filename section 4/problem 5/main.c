#include <stdio.h>
#include <string.h>


void remove_enter(int len, char text[len + 1]);


int main(){

    int location = 0;

    char text[501];
    fgets(text, sizeof(text), stdin);
    remove_enter(strlen(text), text);

    while (1){

        char command[20];
        scanf(" %s", command);

        if (strcmp("###", command) == 0){
            
            printf("%s", text);
            break;

        }else if (strcmp("location", command) == 0){
            
            printf("%d", location);
        
        }else if (strcmp("move", command) == 0){
            
            int n;
            scanf(" %d", &n);

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


void remove_enter(int len, char text[len + 1]){

    if (text[len - 1] == '\n'){
        text[len - 1] = '\0';
    }

}