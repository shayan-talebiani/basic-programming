#include <stdio.h>
#include <string.h>
#include <stdlib.h>


enum Data_Type{

    NUMBER,
    TEXT,
    OBJECT

};

enum Index_State{

    WAITING_FOR_KEY,
    IN_KEY,
    WAITING_FOR_COLON,
    WAITING_FOR_VALUE,
    IN_VALUE,
    WAITING_FOR_COMMA

};

typedef struct Data{

    enum Data_Type type;

    char *key;

    char *value;

    struct Data *front;
    struct Data *down;

} Data;

Data *load_data(char *path);
Data *build_data_tree(char *text, int *index);

void print_data(Data *node, int depth);

int find_depth(Data* data);
void typeof_place(Data* data, char *place);
void valueof_place(Data* data, char *place);

int main(){

    char command[1000];

    fgets(command, sizeof(command), stdin);

    char path[100];
    sscanf(command, " %s", path);

    Data *data = load_data(path);

    while (1){


        fgets(command, sizeof(command), stdin);
        
        char action[1000];
        int i = 0;

        while (command[i] != '\n' && command[i] != '\0' && command[i] != ' ' && command[i] != '\r'){
            
            action[i] = command[i];
            i++;

        }

        action[i] = '\0';
        
        if (strcmp(action, "depth") == 0){
        
            int depth = find_depth(data);
            printf("%d\n", depth);
            
        }else if (strcmp(action, "typeof") == 0 || strcmp(action, "valueof") == 0){
        
            char *place = command + i + 1;

            int j = 0;

            while (place[j] != '\n' && place[j] != '\0' && place[j] != ' ' && place[j] != '\r'){
            
                if (place[j] == '.'){
                    
                    place[j] = '\0';
                
                }
                
                j++;

            }

            place[j] = '\0';
            place[j+1] = '\0';
            


            if (strcmp(action, "typeof") == 0){
            
                typeof_place(data, place); 

            } else {

                valueof_place(data, place);

            }
            
        }else if (strcmp(action, "exit") == 0){
        
            break;
            
        }

    }
    

    return 0;
}


Data *load_data(char *path){

    FILE *file = fopen(path, "r");
    fseek(file, 0, SEEK_END);

    int len = ftell(file);

    rewind(file);

    char *text = (char *) malloc(len + 1);
    fread(text, 1, len, file);
    text[len] = '\0';

    fclose(file);

    int index = 0;

    while (text[index] != '{'){


        if (text[index] == '\0'){
            
            
            return NULL; 
            
        }

        index += 1;

    }

    Data *data = build_data_tree(text, &index);

    return data;
        
}

Data *build_data_tree(char *text, int *index){

    enum Index_State index_state = WAITING_FOR_KEY;

    int first_time = 1;
    Data *first_data = NULL;

    Data *last_complete_data;

    int string_index;

    while (1){
        
        if (index_state == WAITING_FOR_KEY){

            if (text[*index] == '"'){
                
                index_state = IN_KEY;
                string_index = 0;

                if (first_time){
                
                    first_data = (Data *) malloc(sizeof(Data));
                    first_data->key = (char *)malloc(100 * sizeof(char));

                }else{

                    last_complete_data->down = (Data *) malloc(sizeof(Data));
                    last_complete_data->down->key = (char *)malloc(100 * sizeof(char));

                }

            }

            if (text[*index] == '}'){
                
                return first_data;
            
            }


        }else if (index_state == IN_KEY){

            Data *data;

            if(first_time){
                
                data = first_data;
            
            }else{

                data = last_complete_data->down;

            }

            if (text[*index] != '"'){
                    
                data->key[string_index] = text[*index];

            }else{
    
                data->key[string_index] = '\0';
                index_state = WAITING_FOR_COLON;

            }

            string_index++;
            

        }else if (index_state == WAITING_FOR_COLON){

            if (text[*index] == ':'){
                
                index_state = WAITING_FOR_VALUE;

            }
            

        }else if (index_state == WAITING_FOR_VALUE){

            Data *data;

            if(first_time){
                
                data = first_data;
            
            }else{

                data = last_complete_data->down;

            }

            if (text[*index] == '"'){
                    
                data->type = TEXT;
                data->value = (char *)malloc(100 * sizeof(char));
                data->front = NULL;

                string_index = 0;
                index_state = IN_VALUE;

            }else if ((text[*index] >= '0' && text[*index] <= '9') || text[*index] == '-' || text[*index] == '+' || text[*index] == '.'){
                
                data->type = NUMBER;
                data->value = (char *)malloc(100 * sizeof(char));
                data->front = NULL;

                *index -= 1;
                string_index = 0;
                index_state = IN_VALUE;

            }else if (text[*index] == '{'){
                
                data->type = OBJECT;
                data->front = build_data_tree(text, index);

                if (first_time){
                    
                    first_time = 0;

                }

                index_state = WAITING_FOR_COMMA;
                last_complete_data = data;
                data->down = NULL;

            }
            

        }else if (index_state == IN_VALUE){

            Data *data;

            if(first_time){
                
                data = first_data;
            
            }else{

                data = last_complete_data->down;

            }
            

            if (data->type == TEXT){

                if (text[*index] != '"'){
                    
                    data->value[string_index] = text[*index];

                }else {

                    data->value[string_index] = '\0';
                    index_state = WAITING_FOR_COMMA;
                    
                    if(first_time){

                        first_time = 0;

                    }

                    last_complete_data = data;
                    data->down = NULL;

                }
                
                string_index++;

            }else if (data->type == NUMBER){

                if ((text[*index] >= '0' && text[*index] <= '9') || text[*index] == '-' || text[*index] == '+' || text[*index] == '.'){
                    
                    data->value[string_index] = text[*index];
                    
                }else{

                    data->value[string_index] = '\0';
                    index_state = WAITING_FOR_COMMA;
                    *index -= 1;

                    if(first_time){

                        first_time = 0;

                    }                    

                    last_complete_data = data;
                    data->down = NULL;

                }

                string_index++;

            }

        }else if (index_state == WAITING_FOR_COMMA){

            if (text[*index] == ','){
                
                index_state = WAITING_FOR_KEY;
            
            }else if (text[*index] == '}'){
                
                return first_data;
            
            }
            
        }
        
        *index += 1;

    }

}


void print_data(Data *node, int depth) {
    if (node == NULL)
        return;


    for (int i = 0; i < depth; i++) {
        printf("    ");
    }


    if (node->key)
        printf("Key: %s -> ", node->key);


    switch (node->type) {
        case NUMBER:
            printf("Number: %s\n", node->value);
            break;

        case TEXT:
            printf("Text: %s\n", node->value);
            break;

        case OBJECT:
            printf("Object\n");
            break;
    }


    if (node->front)
        print_data(node->front, depth + 1);


    if (node->down)
        print_data(node->down, depth);
}

int find_depth(Data *data){
    
    if (data == NULL){
        
        return 0;

    }

    Data *element = data;

    int depth;
    int max_depth = 0;

    while (element != NULL){
        
        if (element->front == NULL){
           
            depth = 1;
            
        }else {

            depth = 1 + find_depth(element->front);

        }
        

        if (max_depth < depth){
            
            max_depth = depth;

        }
        
        if (element->down != NULL){
            
            element = element->down;

        } else {

            break;

        }

    }
    
    return max_depth;
}

void typeof_place(Data *data, char *place){
    
    if (data == NULL){
        
        printf("No value found for this address!!\n");
        return;

    }

    Data *element = data;

    int len_key = strlen(place);

    while (element != NULL){
        
        if (strcmp(element->key, place) == 0){
            
            if (place[len_key+1] == '\0'){

                if (element->type == NUMBER){
                    
                    printf("INT\n");
                    return;

                }else if (element->type == TEXT){
                    
                    printf("STRING\n");
                    return;

                }else {
                    
                    printf("OBJECT\n");
                    return;

                }
                

            }else {

                if (element->front == NULL){
           
                    printf("No value found for this address!!\n");
                    return;

                }else {

                    typeof_place(element->front, place + len_key + 1);
                    return;
                }

            }
            

        }
        
        
        if (element->down != NULL){
            
            element = element->down;

        } else {

            printf("No value found for this address!!\n");
            return;

        }

    }

}

void valueof_place(Data *data, char *place){
    
    if (data == NULL){
        
        printf("No value found for this address!!\n");
        return;

    }

    Data *element = data;

    int len_key = strlen(place);

    while (element != NULL){
        
        if (strcmp(element->key, place) == 0){
            
            if (place[len_key+1] == '\0'){

                if (element->type == NUMBER){
                    
                    printf("%s\n", element->value);
                    return;

                }else if (element->type == TEXT){
                    
                    printf("%s\n", element->value);
                    return;

                }else {
                    
                    printf("I can not print objects!\n");
                    return;

                }
                

            }else {

                if (element->front == NULL){
           
                    printf("No value found for this address!!\n");
                    return;

                }else {

                    valueof_place(element->front, place + len_key + 1);
                    return;
                }

            }
            

        }
        
        
        if (element->down != NULL){
            
            element = element->down;

        } else {

            printf("No value found for this address!!\n");
            return;

        }

    }

}