#include "lights.h"

void light_set_floor_indicator(void) {
    int floor = elevator_get_floor();                
    if (floor != -1) {  // Double redundancy
        elev_set_floor_indicator(floor);      
    }
}

void light_set_lamp(elev_button_type_t button, int floor, int value) {
    elev_set_button_lamp(button, floor, value);
}

void light_shut_at_floor(int floor) {
    if (floor != N_FLOORS-1) {
        light_set_lamp(BUTTON_CALL_UP, floor, 0);
    }
    if (floor != 0) {
        light_set_lamp(BUTTON_CALL_DOWN, floor, 0);
    }
    light_set_lamp(BUTTON_COMMAND, floor, 0);
}

void light_shut_all(void) {
    for (int i = 0; i < N_FLOORS; i++) {
        light_shut_at_floor(i);
    }
}

void light_set_stop_lamp(int value) {
    elev_set_stop_lamp(value);
}