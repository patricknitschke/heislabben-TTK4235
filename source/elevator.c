#include "elevator.h"
#include "lights.h"
#include "door.h"
#include <unistd.h>

static Elevator elevator;

// Start downwards, stop at defined state
int start(void){
    set_elev_direction(DIRN_DOWN);

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

void station_stop(elev_motor_direction_t dir) {
    elev_set_motor_direction(DIRN_STOP);    
}

void continue_driving(){
    elev_set_motor_direction(get_elev_direction());
}

void emergency_stop(){
    elev_set_motor_direction(DIRN_STOP);
    for(int i = 0; i<6; i++){
        pop_queue(i);
    }
}
