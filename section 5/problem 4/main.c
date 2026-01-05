#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Car{
    
    char plate[20];
    char color[20];

} Car;

typedef struct Lane{

    Car *car;

    struct Lane *rest_lane;

} Lane;


void print_road(int road_car_counts[2], Lane *road[2]);

void add_new_car(int road_car_counts[2], Lane *road[2]);
void add_car(int road_car_counts[2], int lane_index, Lane *road[2], int k, Car *new_car);
void delete_black_car(int road_car_counts[2], Lane *road[2]);
void delete_car(int road_car_counts[2], int lane_index, Lane *lane);
void change_car(int road_car_counts[2], Lane *road[2]);
void overtake(int road_car_counts[2], Lane *road[2]);

Lane *check_plate(int road_car_counts[2], Lane *road[2], char plate[20], int *lane_index, int *k);


int main(){

    Lane *road[2];
    int road_car_counts[2];

    for (int i = 0; i < 2; i++){
        road_car_counts[i] = 0;
    }

    while (1){
        
        char command[20];
        scanf(" %s", &command);

        if (strcmp("EXIT", command) == 0){
            
            print_road(road_car_counts, road);
            break;

        }else if (strcmp("add", command) == 0){
            
            add_new_car(road_car_counts, road);

        }else if (strcmp("delete", command) == 0){
            
            delete_black_car(road_car_counts, road);

        }else if (strcmp("change", command) == 0){
            
            change_car(road_car_counts, road);

        }else if (strcmp("overtake", command) == 0){
            
            overtake(road_car_counts, road);

        }else if (strcmp("p", command) == 0){
            
            print_road(road_car_counts, road);

        }
        

    }
    



    return 0;
}


void print_road(int road_car_counts[2], Lane *road[2]){

    for (int i = 0; i < 2; i++){
        
        printf("lane %d:\n", i);

        Lane *lane = road[i]; 

        for (int j = 0; j < road_car_counts[i]; j++){

            printf("%s (%s)\n", lane->car->plate, lane->car->color);
            lane = lane->rest_lane;

        }

        if (i == 0){
            printf("**********\n");
        }
        

    }

}


void add_new_car(int road_car_counts[2], Lane *road[2]){
    
    Car *new_car = (Car *) malloc(sizeof(Car));
    int lane_index;
    int k;

    scanf(" %d", &lane_index);
    scanf(" %d", &k);
    scanf(" %s", &(new_car->plate));
    scanf(" %s", &(new_car->color));

    if (k < 1 || k > road_car_counts[lane_index] + 1){
        
        printf("an invalid number is given\n");
        free(new_car);
        return;

    }


    int lane_index_founded;
    int k_founded;
    Lane *place = check_plate(road_car_counts, road, new_car->plate, &lane_index_founded, &k_founded);
    
    if (NULL != place){
        
        printf("this plate was already given\n");
        free(new_car);
        return;
    
    }

    add_car(road_car_counts, lane_index, road, k, new_car);

}

void add_car(int road_car_counts[2], int lane_index, Lane *road[2], int k, Car *new_car){

    if (road_car_counts[lane_index] == 0){
        
        road[lane_index] = (Lane *)malloc(sizeof(Lane));
    
    }
    
    Lane *lane = road[lane_index];

    for (int i = 1; i < k; i++){

        lane = lane->rest_lane;

    }

    Lane *rest_lane = (Lane *)malloc(sizeof(Lane));

    rest_lane->car = lane->car;
    rest_lane->rest_lane = lane->rest_lane; 

    lane->rest_lane = rest_lane;
    lane->car = new_car;

    road_car_counts[lane_index]++;

}

void delete_black_car(int road_car_counts[2], Lane *road[2]){

    for (int i = 0; i < 2; i++){

        Lane *lane = road[i]; 

        for (int j = 0; j < road_car_counts[i]; j++){

            if (strcmp(lane->car->color, "black") == 0){
                
                delete_car(road_car_counts, i, lane);
                j--;
                
            }else{

                lane = lane->rest_lane;

            }


        }
        
    }

}

void delete_car(int road_car_counts[2], int lane_index, Lane *lane){

    Lane *rest_lane = lane->rest_lane;

    free(lane->car);

    lane->car = rest_lane->car;
    lane->rest_lane = rest_lane->rest_lane;

    free(rest_lane);

    road_car_counts[lane_index]--;

}

void change_car(int road_car_counts[2], Lane *road[2]){

    char plate[20];
    scanf(" %s", plate);

    int lane_index;
    int k;

    Lane *place = check_plate(road_car_counts, road, plate, &lane_index, &k);

    if (place == NULL){

        printf("Car not found\n");
        return;
    
    }

    if (k > road_car_counts[(lane_index+1)%2] + 1){

        k = road_car_counts[(lane_index+1)%2] + 1;
    
    }
    

    Car *car = (Car *) malloc(sizeof(Car));

    *car = *(place->car);

    add_car(road_car_counts, (lane_index+1)%2, road, k, car);
    delete_car(road_car_counts, lane_index, place);

}

void overtake(int road_car_counts[2], Lane *road[2]){

    char plate[20];
    scanf(" %s", plate);

    int num;
    scanf(" %d", &num);

    if (num < 1){
        
        printf("an invalid number is given\n");
        return;
    }

    int lane_index;
    int k;

    Lane *place = check_plate(road_car_counts, road, plate, &lane_index, &k);

    if (place == NULL){

        printf("Car not found\n");
        return;
    
    }

    int new_k = k - num;

    Car *car = (Car *) malloc(sizeof(Car));

    *car = *(place->car);


    add_car(road_car_counts, lane_index, road, new_k, car);
    delete_car(road_car_counts, lane_index, place);


}


Lane *check_plate(int road_car_counts[2], Lane *road[2], char plate[20], int *lane_index, int *k){

    Lane *lane;

    for (int i = 0; i < 2; i++){

        lane = road[i];
    
        for (int j = 0; j < road_car_counts[i]; j++){
            
            if (strcmp(lane->car->plate, plate) == 0){
                
                *lane_index = i;
                *k = j + 1;
                return lane;
                
            }
            
            lane = lane->rest_lane;

        }

    }
    

    return NULL;
}
