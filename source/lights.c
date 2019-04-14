#include "lights.h"

void floor_light_set(void) {
    int floor = get_elev_floor();                
    if (floor != -1) {  // Double redundancy
        elev_set_floor_indicator(floor);      
    }
}

void set_lamp(elev_button_type_t button, int floor, int value) {
    elev_set_button_lamp(button, floor, value);
}

void shut_lights_at_floor(int floor) {
    if (floor != N_FLOORS-1) {
        set_lamp(BUTTON_CALL_UP, floor, 0);
    }
    if (floor != 0) {
        set_lamp(BUTTON_CALL_DOWN, floor, 0);
    }
    set_lamp(BUTTON_COMMAND, floor, 0);
}

void shut_all_lights(void) {
    for (int i = 0; i < 4; i++){
        if (i != N_FLOORS-1) {
            set_lamp(BUTTON_CALL_UP, i, 0);
        }
        if (i != 0) {
            set_lamp(BUTTON_CALL_DOWN, i, 0);
        }
        set_lamp(BUTTON_COMMAND, i, 0);
    }
}

void set_stoplight(int value){
    elev_set_stop_lamp(value);
}