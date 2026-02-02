#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <openssl/sha.h>

typedef struct Path_List{

    char *path;
    
    struct Path_List *rest;

} Path_List;

typedef struct Unique_Files_List{

    char *name;
    unsigned char *hash;

    int path_number;
    Path_List *path_list; 
    
    struct Unique_Files_List *rest;

} Unique_Files_List;


void set_file_list(Unique_Files_List *unique_files_list, char *path, int *unique_files_count);
void add_new_unique_file(Unique_Files_List *unique_files_list, char *file_hash, char *file_name, char *file_path, int *unique_files_count);
void add_new_repeated_file(Unique_Files_List *this_file, char *file_path);
Unique_Files_List *check_new_unique_file(Unique_Files_List *unique_files_list, char *file_hash, char *file_name, int *unique_files_count);

unsigned char *file2hash(char *path);


void print_douplicated_files(Unique_Files_List *unique_files_list, int unique_files_count);


int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Error: Please provide a folder name.\nUsage: %s <folder_path>\n", argv[0]);
        return 1;
    }

    Unique_Files_List *unique_files_list = (Unique_Files_List *) malloc(sizeof(Unique_Files_List));
    int unique_files_count = 0;

    set_file_list(unique_files_list, argv[1], &unique_files_count);

    print_douplicated_files(unique_files_list, unique_files_count);

    return 0;
}


void set_file_list(Unique_Files_List *unique_files_list, char *path, int *unique_files_count){
    
    DIR *dir = opendir(path);

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL){

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 ){
            continue;
        }

        char *file_name = (char *) malloc(strlen(entry->d_name) + 1);  

        strcpy(file_name, entry->d_name);

        char *new_path = (char *) malloc(strlen(path) + strlen(entry->d_name) + 2);

        strcpy(new_path, path);
        strcat(new_path, "/");
        strcat(new_path, file_name);

        DIR *dir_existing_check;

        if ((dir_existing_check = opendir(new_path)) == NULL){
        
            Unique_Files_List *this_file;
            unsigned char *file_hash = file2hash(new_path);

            if ((this_file = check_new_unique_file(unique_files_list, file_hash, file_name, unique_files_count)) == NULL){
                
                add_new_unique_file(unique_files_list, file_hash, file_name, new_path, unique_files_count);
            
            }else{
                
                add_new_repeated_file(this_file, new_path);

            }
            
        }else{

            closedir(dir_existing_check);
            set_file_list(unique_files_list, new_path, unique_files_count);

        } 

    }

    closedir(dir);

}

void add_new_unique_file(Unique_Files_List *unique_files_list, char *file_hash, char *file_name, char *file_path, int *unique_files_count){
    
    Unique_Files_List *unique_file = unique_files_list;

    for (int  i = 0; i < *unique_files_count; i++){
        
        if (strcmp(file_name, unique_file->name) < 0){

            Unique_Files_List* unique_file_rest  = (Unique_Files_List *) malloc(sizeof(Unique_Files_List));

            unique_file_rest->rest = unique_file->rest;
            unique_file_rest->hash = unique_file->hash;
            unique_file_rest->name = unique_file->name;
            unique_file_rest->path_number = unique_file->path_number;
            unique_file_rest->path_list = unique_file->path_list;

            unique_file->rest = unique_file_rest;
            unique_file->hash = file_hash;
            unique_file->name = file_name;
            unique_file->path_number = 1;
            unique_file->path_list = (Path_List *) malloc(sizeof(Path_List));
            unique_file->path_list->path = file_path;
            unique_file->path_list->rest = (Path_List *) malloc(sizeof(Path_List));

            *unique_files_count += 1;
            return;

        }
        
        unique_file = unique_file->rest;

    }

    unique_file->rest = (Unique_Files_List *) malloc(sizeof(Unique_Files_List));
    unique_file->hash = file_hash;
    unique_file->name = file_name;
    unique_file->path_number = 1;
    unique_file->path_list = (Path_List *) malloc(sizeof(Path_List));
    unique_file->path_list->path = file_path;
    unique_file->path_list->rest = (Path_List *) malloc(sizeof(Path_List));

    *unique_files_count += 1;

}

void add_new_repeated_file(Unique_Files_List *this_file, char *file_path){

    Path_List *path  = this_file->path_list;

    for (int  i = 0; i < this_file->path_number; i++){
        
        if (strcmp(file_path, path->path) < 0){

            Path_List *path_rest = (Path_List *) malloc(sizeof(Path_List));

            path_rest->path = path->path;
            path_rest->rest = path->rest;

            path->path = file_path;
            path->rest = path_rest;

            this_file->path_number += 1;
            return;

        }
        
        path = path->rest;

    }
    
    path->path = file_path;
    path->rest = (Path_List *) malloc(sizeof(Path_List));
    
    this_file->path_number += 1; 

}

Unique_Files_List *check_new_unique_file(Unique_Files_List *unique_files_list, char *file_hash, char *file_name, int *unique_files_count){

    Unique_Files_List *unique_file = unique_files_list;

    for (int i = 0; i < *unique_files_count; i++){

        if (memcmp(unique_file->hash, file_hash, SHA256_DIGEST_LENGTH) == 0 && strcmp(unique_file->name, file_name) == 0){

            return unique_file;
        
        }

        unique_file = unique_file->rest;

    }

    return NULL;
}


unsigned char *file2hash(char *path){

    FILE *file = fopen(path, "rb");
    if (!file) return NULL;

    unsigned char data[1024];
    unsigned char *hash = (unsigned char *) malloc(SHA256_DIGEST_LENGTH * sizeof(unsigned char));
    SHA256_CTX ctx;

    SHA256_Init(&ctx);

    size_t bytes;
    while ((bytes = fread(data, 1, 1024, file)) != 0)
        SHA256_Update(&ctx, data, bytes);

    SHA256_Final(hash, &ctx);

    fclose(file);
    return hash;
}


void print_douplicated_files(Unique_Files_List *unique_files_list, int unique_files_count){

    printf("Duplicated Files List:\n");

    Unique_Files_List *unique_file = unique_files_list;

    int k = 0;

    for (int i = 0; i < unique_files_count; i++){

        if (unique_file->path_number > 1){

            printf("%d.(%s)\n", ++k, unique_file->name);

            

            Path_List *path_list = unique_file->path_list;

            for (int j = 0; j < unique_file->path_number; j++){
                
                printf("%s\n", path_list->path);

                path_list = path_list->rest;

            }

            printf("\n");
        
        }

        unique_file = unique_file->rest;

    }
    
}