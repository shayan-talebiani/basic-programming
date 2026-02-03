#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Record{
    
    int id;
    char name[50];
    int age;
    char filed[50];


} Record;


void add_record(char *path);
void read_all_records(char *path);
void update_record(char *path);
void delete_record(char *path);


int main(){

    char *path = "database.dat";

    FILE *database;

    if ((database = fopen(path, "rb")) == NULL){
        
        database = fopen(path, "wb");
        fclose(database);
    
    }else{

        fclose(database);

    }
    

    while (1){
        
        char command[100];
        scanf("%s", command);
        getchar();getchar();

        if (strcmp(command, "INSERT") == 0){

            add_record(path);
            
        }else if (strcmp(command, "SELECT") == 0){

            read_all_records(path);            
            
        }else if (strcmp(command, "UPDATE") == 0){

            update_record(path);
            
        }else if (strcmp(command, "DELETE") == 0){

            delete_record(path);
            
        }else if (strcmp(command, "exit") == 0){

            break;
            
        }
        

    }
    

    return 0;
}


void add_record(char *path){

    FILE *database = fopen(path, "rb+");

    Record record;
    scanf("student( %[^,], %d, %[^)])", record.name, &record.age, record.filed);
    getchar();getchar();

    Record element;

    record.id = 0;

    while (fread(&element, sizeof(Record), 1, database) != 0){
        
        record.id = element.id;

    }

    record.id++;

    fwrite(&record, sizeof(Record), 1, database);

    fclose(database);

}

void read_all_records(char *path){

    FILE *database = fopen(path, "rb+");

    Record element;

    printf("----------\n");
    printf("ID / name / age / field\n");

    while (fread(&element, sizeof(Record), 1, database) != 0){
        
        printf("%d %s %d %s\n", element.id, element.name, element.age, element.filed);

    }

    printf("----------\n");
    
    fclose(database);

}

void update_record(char *path){

    FILE *database = fopen(path, "rb+");

    Record record;
    scanf("ID: %d", &record.id);
    getchar();getchar();
    scanf("student( %[^,], %d, %[^)])", record.name, &record.age, record.filed);
    getchar();getchar();

    Record element;
    int founded = 0;

    while (fread(&element, sizeof(Record), 1, database) != 0){
        
        if(element.id == record.id){

            printf("Record updated.\n");
            founded = 1;
            
            fseek(database, - (int)sizeof(Record), SEEK_CUR);
            fwrite(&record, sizeof(Record), 1, database);
            fflush(database);
            
            break;
        }

    }
    

    if (founded == 0){

        printf("ID not found!\n");
    
    }
    

    fclose(database);

}

void delete_record(char *path){

    FILE *database = fopen(path, "rb+");
    FILE *new_database = fopen("newdatabase.dat", "wb+");

    int id;
    scanf("ID: %d", &id);
    getchar();getchar();

    Record element;
    int founded = 0;

    while (fread(&element, sizeof(Record), 1, database) != 0){
        
        if(element.id == id){

            printf("Record deleted.\n");
            founded = 1;

        }else{

            

            fwrite(&element, sizeof(Record), 1, new_database);

        }

    }
    

    if (founded == 0){

        printf("ID not found!\n");
    
    }
    

    fclose(database);
    remove(path);

    fclose(new_database);
    rename("newdatabase.dat", path);


}
