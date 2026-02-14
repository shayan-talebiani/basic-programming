#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


typedef struct {
    char name[100];
    char artist[100];
    int duration;      // in seconds
    int isFavorite;
} Song;


void add_song(char *line, char *playlist_path, char *output_path);
int duration_string2number(char *duration_string);
void delete_song(char *line, char *playlist_path, char *output_path);
void star_song(char *line, char *playlist_path, char *output_path);
void unstar_song(char *line, char *playlist_path, char *output_path);
void list_all_songs(char *playlist_path, char *output_path);
void list_favorites_songs(char *playlist_path, char *output_path);
void playlist_signature(char *playlist_path, char *output_path);
int str2hash(char *str);
void playlist_entropy(char *playlist_path, char *output_path);
void sort_songs(char *playlist_path, char *output_path, int (cmp2songs)(Song*, Song*));
int cmp2songs_by_name(Song* a, Song* b);
int cmp2songs_by_artist(Song* a, Song* b);
int cmp2songs_by_duration(Song* a, Song* b);

void setup_file(char *path);


int main(){

    char *playlist_path = "playlist.dat";
    char *output_path = "output.txt";

    setup_file(playlist_path);
    setup_file(output_path);

    while (1){

        char line[300];
        fgets(line, 300, stdin);
        
        if (strcmp(line, "\0") == 0 || strcmp(line, "\n\0") == 0 || strcmp(line, "\r\n\0") == 0){

            continue;

        }
        

        char commend[100];
        sscanf(line, " %s", commend);

        if (strcmp(commend, "add") == 0){

            add_song(line, playlist_path, output_path);

        }else if (strcmp(commend, "exit") == 0){
            
            break;

        }else if (strcmp(commend, "delete") == 0){
            
            delete_song(line, playlist_path, output_path);

        }else if (strcmp(commend, "star") == 0){
            
            star_song(line, playlist_path, output_path);

        }else if (strcmp(commend, "unstar") == 0){
            
            unstar_song(line, playlist_path, output_path);

        }else if (strcmp(commend, "list") == 0){
            
            list_all_songs(playlist_path, output_path);

        }else if (strcmp(commend, "filter_favorites") == 0){
            
            list_favorites_songs(playlist_path, output_path);

        }else if (strcmp(commend, "playlist_signature") == 0){
            
            playlist_signature(playlist_path, output_path);

        }else if (strcmp(commend, "playlist_entropy") == 0){
            
            playlist_entropy(playlist_path, output_path);

        }else if (strcmp(commend, "sort_name") == 0){
            
            sort_songs(playlist_path, output_path, cmp2songs_by_name);

        }else if (strcmp(commend, "sort_artist") == 0){
            
            sort_songs(playlist_path, output_path, cmp2songs_by_artist);

        }else if (strcmp(commend, "sort_duration") == 0){
            
            sort_songs(playlist_path, output_path, cmp2songs_by_duration);

        }
        
    }

    return 0;

}


void add_song(char *line, char *playlist_path, char *output_path){

    int invalid = 0;
    char *tokens[4];

    FILE *output_file = fopen(output_path, "a");

    if ((tokens[0] = strtok(line, " ")) != NULL){
        
        int i = 1;

        while ( (tokens[i] = strtok(NULL, " ")) != NULL){
 
            if (i > 3){
                
                invalid = 1;
                break;

            }

            i++; 
            
        }

        if (i != 4){
            
            invalid = 1;
        
        }
        

    }else {

        invalid = 1;

    }

    if (invalid){
        
        fprintf(output_file, "Invalid add command.\n");
        fclose(output_file);
        return;

    }

    char duration_string[50];
    sscanf(tokens[3], " %s", duration_string);
    
    int duration = duration_string2number(duration_string);

    if (duration == -1){
        
        fprintf(output_file, "Invalid duration format: %s\n", duration_string);
        fclose(output_file);
        return;      

    }
    
    Song song;
    strcpy(song.name, tokens[1]);
    strcpy(song.artist, tokens[2]);    
    song.duration = duration;
    song.isFavorite = 0;

    FILE *playlist_file = fopen(playlist_path, "ab");
    fwrite(&song, sizeof(Song), 1, playlist_file);
    fclose(playlist_file);

    fprintf(output_file, "Song added: %s by %s\n", song.name, song.artist);
    fclose(output_file);

}

int duration_string2number(char *duration_string){
    
    int i = 0;
    int colan_existing = 0;
    int colan_index;

    while (duration_string[i] != '\0'){    

        if (duration_string[i] == ':' && i <= 2 && i != 0){

            if (colan_existing){
                
                return -1;

            }else{
                
                colan_index = i;
                colan_existing = 1;
            
            }
            
        }else if (!('0' <= duration_string[i] && duration_string[i] <= '9')){

            return -1;

        }
        
        i++;

    }

    int duration_string_last_i = i - 1;
    
    int duration_number = 0;

    if (colan_existing){
        
        if (duration_string_last_i - colan_index == 1){
            
            int i = 0;

            while (i < colan_index){

                duration_number = duration_number * 10 + (int)(duration_string[i] - '0');
                i++;
                
            }

            if (duration_number > 60){
                
                return -1;
                
            }

            duration_number = duration_number * 60 + (int)(duration_string[i + 1] - '0');
            

        }else if (duration_string_last_i - colan_index == 2){
            
            int i = 0;

            while (i < colan_index){

                duration_number = duration_number * 10 + (int)(duration_string[i] - '0');
                i++;

            }

            int second = 10 * (int)(duration_string[i + 1] - '0') + (int)(duration_string[i + 2] - '0');

            if (duration_number > 60 || second > 60){
                
                return -1;
                
            }

            duration_number = duration_number * 60 + second;            


        } else {

            return -1;

        }
        

    }else{

        int i = 0;

        while (duration_string[i] != '\0'){

            duration_number = duration_number * 10 + (int)(duration_string[i] - '0');
            i++;

        }
        

    }
    
    return duration_number; 
}

void delete_song(char *line, char *playlist_path, char *output_path){

    char *new_playlist_path = "temp.dat";

    FILE *playlist_file = fopen(playlist_path, "rb");
    FILE *new_playlist_file = fopen(new_playlist_path, "wb");

    char song_name[100];
    sscanf(line, "delete %s", song_name);

    Song element;
    int found = 0;

    while (fread(&element, sizeof(Song), 1, playlist_file)){
        
        if (strcmp(element.name, song_name) == 0){

            found = 1;

        }else{

            fwrite(&element, sizeof(Song), 1, new_playlist_file);

        }
        
    }

    fclose(playlist_file);
    fclose(new_playlist_file);
    
    remove(playlist_path);
    rename(new_playlist_path, playlist_path);

    FILE *output_file = fopen(output_path, "a");

    if (found){
        
        fprintf(output_file, "Deleted: %s\n", song_name);

    }else{

        fprintf(output_file, "Song not found: %s\n", song_name);

    }
    
    fclose(output_file);

}

void star_song(char *line, char *playlist_path, char *output_path){

    char *new_playlist_path = "temp.dat";

    FILE *playlist_file = fopen(playlist_path, "rb");
    FILE *new_playlist_file = fopen(new_playlist_path, "wb");

    char song_name[100];
    sscanf(line, "star %s", song_name);

    Song element;
    int found = 0;

    while (fread(&element, sizeof(Song), 1, playlist_file)){
        
        if (strcmp(element.name, song_name) == 0 && found == 0){

            element.isFavorite = 1;
            fwrite(&element, sizeof(Song), 1, new_playlist_file);
            found = 1;

        }else{

            fwrite(&element, sizeof(Song), 1, new_playlist_file);

        }
        
    }

    fclose(playlist_file);
    fclose(new_playlist_file);
    
    remove(playlist_path);
    rename(new_playlist_path, playlist_path);

    if (found){
        
        FILE *output_file = fopen(output_path, "a");
    
        fprintf(output_file, "Starred: %s\n", song_name);
    
        fclose(output_file);
    
    }
    
}

void unstar_song(char *line, char *playlist_path, char *output_path){

    char *new_playlist_path = "temp.dat";

    FILE *playlist_file = fopen(playlist_path, "rb");
    FILE *new_playlist_file = fopen(new_playlist_path, "wb");

    char song_name[100];
    sscanf(line, "unstar %s", song_name);

    Song element;
    int found = 0;

    while (fread(&element, sizeof(Song), 1, playlist_file)){
        
        if (strcmp(element.name, song_name) == 0 && found == 0){

            element.isFavorite = 0;
            fwrite(&element, sizeof(Song), 1, new_playlist_file);
            found = 1;

        }else{

            fwrite(&element, sizeof(Song), 1, new_playlist_file);

        }
        
    }

    fclose(playlist_file);
    fclose(new_playlist_file);
    
    remove(playlist_path);
    rename(new_playlist_path, playlist_path);

    if (found){
        
        FILE *output_file = fopen(output_path, "a");
    
        fprintf(output_file, "Unstarred: %s\n", song_name);
    
        fclose(output_file);
    
    }
    
}

void list_all_songs(char *playlist_path, char *output_path){

    FILE *playlist_file = fopen(playlist_path, "rb");
    FILE *output_file = fopen(output_path, "a");

    Song element;
    int found = 0;

    while (fread(&element, sizeof(Song), 1, playlist_file)){
        
        if (found == 0){
            
            found = 1;

        }
        
        char *favorite_mode_str;

        if (element.isFavorite == 0){
        
            favorite_mode_str = "Normal";

        }else{

            favorite_mode_str = "Favorite";

        }

        fprintf(output_file, "%s | %s | %d | %s\n", element.name, element.artist, element.duration, favorite_mode_str);
        
    }

    fclose(playlist_file);

    if (found == 0){
            
        fprintf(output_file, "Playlist is empty.\n");

    }

    fclose(output_file);

}

void list_favorites_songs(char *playlist_path, char *output_path){

    FILE *playlist_file = fopen(playlist_path, "rb");
    FILE *output_file = fopen(output_path, "a");

    Song element;
    int found = 0;

    while (fread(&element, sizeof(Song), 1, playlist_file)){
        
        if (element.isFavorite){ 

            if (found == 0){
                
                found = 1;

            }

            fprintf(output_file, "%s | %s | %d | Favorite\n", element.name, element.artist, element.duration);
        
        }

    }

    fclose(playlist_file);

    if (found == 0){
            
        fprintf(output_file, "No favorites found.\n");

    }

    fclose(output_file);

}

void playlist_signature(char *playlist_path, char *output_path){

    FILE *playlist_file = fopen(playlist_path, "rb");
    FILE *output_file = fopen(output_path, "a");

    unsigned int signature = 0;

    Song element;
    unsigned int song_hash = 0;
    int i = 0;

    while (fread(&element, sizeof(Song), 1, playlist_file)){
        
        song_hash = 0;

        song_hash += ( unsigned int) 31 * ( unsigned int) str2hash(element.name);
        song_hash += ( unsigned int) 17 * ( unsigned int) str2hash(element.artist); 
        song_hash += ( unsigned int) 13 * ( unsigned int) element.duration; 
        song_hash += ( unsigned int) 7 * ( unsigned int) element.isFavorite; 
        signature ^= (song_hash << (unsigned int) (i % 16)); 

        i++;

    }

    fclose(playlist_file);

    fprintf(output_file, "Playlist signature: %u\n", signature);

    fclose(output_file);


}

int str2hash(char *str){

    int hash = 0;

    int i = 0;

    while (str[i] != '\0'){

        hash += ((int) str[i]) * (i + 1);
        i++;

    }
    
    return hash;

}

void playlist_entropy(char *playlist_path, char *output_path){

    FILE *playlist_file = fopen(playlist_path, "rb");
    FILE *output_file = fopen(output_path, "a");

    fseek(playlist_file, 0, SEEK_END);
    int songs_count = ftell(playlist_file) / sizeof(Song);
    rewind(playlist_file);

    int artists_count = 0;
    int artists_songs_count[songs_count];
    char artists_names[songs_count][100];

    Song element;

    int i = 0;

    while (fread(&element, sizeof(Song), 1, playlist_file)){
        
        int new = 1;

        for (int j = 0; j < artists_count; j++){

            if (strcmp(artists_names[j], element.artist) == 0){

                artists_songs_count[j]++;
                new = 0;
                break;
            
            }
            
        }

        if (new){
            
            strcpy(artists_names[artists_count], element.artist);
            artists_songs_count[artists_count] = 1;
            artists_count++;

        }
        
        i++;

    }

    fclose(playlist_file);

    double entropy = 0;

    for (int i = 0; i < artists_count; i++){

        double p = ((double)artists_songs_count[i]) / ((double)songs_count);
        entropy += p * log2(p);
        
    }
    
    entropy = -entropy;

    if (songs_count > 0 && entropy != 0){

        fprintf(output_file, "Playlist entropy: %.3lf\n", entropy);
    
    }else{

        fprintf(output_file, "Playlist entropy: %.3lf\n", (double)0);

    }
    
    fclose(output_file);

}

void sort_songs(char *playlist_path, char *output_path, int(cmp2songs)(Song *, Song *)){

    char *new_playlist_path = "temp.dat";

    FILE *playlist_file = fopen(playlist_path, "rb");
    FILE *new_playlist_file = fopen(new_playlist_path, "w");

    fseek(playlist_file, 0, SEEK_END);
    int songs_count = ftell(playlist_file) / sizeof(Song);
    rewind(playlist_file);

    int writed_songs[songs_count];

    for (int i = 0; i < songs_count; i++){

        writed_songs[i] = 0;

    }
 
    
    Song element;

    for (int i = 0; i < songs_count; i++){

        int first_song = 1;
        Song *song = NULL;
        int index;

        for (int j = 0; j < songs_count; j++){

            fread(&element, sizeof(Song), 1, playlist_file);

            if (writed_songs[j] == 0 && cmp2songs(&element, song) == 1){

                if (first_song){
                    
                    song = (Song*) malloc(sizeof(Song));
                    
                }

                *song = element;
                index = j;

            }
            
            
        }

        fwrite(song, sizeof(Song), 1, new_playlist_file);
        writed_songs[index] = 1;

        free(song);
        rewind(playlist_file);

    }

    fclose(playlist_file);
    fclose(new_playlist_file);

    remove(playlist_path);
    rename(new_playlist_path, playlist_path);

    FILE *output_file = fopen(output_path, "a");

    if (cmp2songs_by_name == cmp2songs){
        
        fprintf(output_file, "Sorted by name.\n");

    }else if (cmp2songs_by_artist == cmp2songs){

        fprintf(output_file, "Sorted by artist.\n");

    }else{

        fprintf(output_file, "Sorted by duration.\n");

    }
    
    fclose(output_file);


}

int cmp2songs_by_name(Song* a, Song* b){
    
    if (a == NULL){
        
        return -1;

    }
    
    if (b == NULL){
        
        return 1;

    }

    if (strcmp(a->name, b->name) < 0){
        
        return 1;

    } else if (strcmp(a->name, b->name) > 0){

        return -1;

    } else {

        if (strcmp(a->artist, b->artist) < 0){
            
            return 1;

        } else {

            return -1;

        }

    }

}

int cmp2songs_by_artist(Song* a, Song* b){
    
    if (a == NULL){
        
        return -1;

    }
    
    if (b == NULL){
        
        return 1;

    }
    
    if (strcmp(a->artist, b->artist) < 0){
        
        return 1;

    } else if (strcmp(a->artist, b->artist) > 0){

        return -1;

    } else {

        if (strcmp(a->name, b->name) < 0){
            
            return 1;

        } else {

            return -1;

        }

    }

}

int cmp2songs_by_duration(Song* a, Song* b){

    if (a == NULL){
        
        return -1;

    }
    
    if (b == NULL){
        
        return 1;

    }

    if (a->duration < b->duration){
        
        return 1;
        
    } else if (a->duration > b->duration){
        
        return -1;
        
    } else {
    
        if (strcmp(a->artist, b->artist) < 0){
            
            return 1;

        } else if (strcmp(a->artist, b->artist) > 0){

            return -1;

        } else {

            if (strcmp(a->name, b->name) < 0){
                
                return 1;

            } else {

                return -1;

            }

        }

    }

}

void setup_file(char *path){

    FILE *file;

    if ((file = fopen(path, "rb")) == NULL){
        
        file = fopen(path, "wb");
        fclose(file);
    
    }else{

        fclose(file);

    }
}