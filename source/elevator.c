#include "elevator.h"
#include <unistd.h>


struct Elevator elevator;

int start(void){
    for( int i = 0; i<6 ; i++){
        pop_queue(i);
    }
    int floor = elev_get_floor_sensor_signal();
    //motor_dir already set direction up from main() 
        
    while(floor==-1){
        floor = elev_get_floor_sensor_signal();
    }

    elev_set_motor_direction(DIRN_STOP);
    elevator.dir = DIRN_STOP;
    set_elevator();
    return floor;
    
}

void set_elevator(){
    if (elev_get_floor_sensor_signal() != -1) {
        elevator.floor = elev_get_floor_sensor_signal();
    }
    if (elevator.floor != -1){
        elevator.valid_position = true;
    }
    else{
        elevator.valid_position = false;
    }
}

void setDirection(elev_motor_direction_t dir){
    elevator.dir = dir;
}


void elevator_rest(){
    if (check_empty_queue()){
        elev_set_motor_direction(DIRN_STOP);
    }
}

struct Elevator* getElevator() {
    return &elevator;
}

void station_stop(elev_motor_direction_t direction){
    elev_set_motor_direction(DIRN_STOP);
}

void floor_light_set(){
}



elev_motor_direction_t getDirection(){
    return elevator.dir;
}