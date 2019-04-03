#include "elevator.h"
#include <unistd.h>


Elevator elevator;

Elevator* getElevator() {
    return &elevator;
}

int start(void){
    for (int i = 0; i < 6; i++) {
        pop_queue(i);
    }
    int floor = elev_get_floor_sensor_signal();
        
    while (floor == -1) {
        floor = elev_get_floor_sensor_signal();
    }
    set_elev_floor();
    set_elev_direction(DIRN_STOP);
    return floor;
}

void set_elev_floor() {
    if (elev_get_floor_sensor_signal() != -1) {
        elevator.floor = elev_get_floor_sensor_signal();
        floor_light_set();
    }
}

int get_elev_floor(){
    return elevator.floor;
}

void set_elev_direction(elev_motor_direction_t dir) {
    elevator.dir = dir;
    elev_set_motor_direction(dir);
}

elev_motor_direction_t get_elev_direction() {
    return elevator.dir;
}

void elevator_rest() {
    if (queue_count() == 0){
        elev_set_motor_direction(DIRN_STOP);
    }
}

void station_stop(elev_motor_direction_t dir, int start_time) {
    set_elev_direction(DIRN_STOP);    
    //if(timer_3_seconds(start_time) == 1){
    set_elev_direction(dir);
   //} 
}

void floor_light_set() {
    int floor = elevator.floor;                //denne slår seg veldig vrang. Prøver å sette lys til -1!!! Programmet krasjer...
    
    if(floor!=-1){
        elev_set_floor_indicator(floor);       //dette gjorde susen! Egentlig skal ikke elevator.floor kunne gi -1, men den gjør altså det engang i blant...
    }
}


void emergency_stop(){
    elev_set_motor_direction(DIRN_STOP);
}

void continue_driving(){
    elev_set_motor_direction(get_elev_direction());
}


int timer_3_seconds(int start_time){
    if(clock()/CLOCKS_PER_SEC - start_time/CLOCKS_PER_SEC >3){
        return 1;
    }
    return 0;
}