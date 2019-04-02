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

void station_stop() {
    set_elev_direction(DIRN_STOP);
    sleep(1);
}

void floor_light_set() {
    int floor = elevator.floor;                //denne slår seg veldig vrang. Prøver å sette lys til -1!!! Programmet krasjer...
    elev_set_floor_indicator(floor);
}