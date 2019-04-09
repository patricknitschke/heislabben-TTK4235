#include "lights.h"

void kill_all_lights(){  //ICE - Turn off all lights
    for(int i = 0; i<4; i++){
        if(i != 3){
            elev_set_button_lamp(BUTTON_CALL_UP, i, 0);
        }
        if(i != 0){
            elev_set_button_lamp(BUTTON_CALL_DOWN, i, 0);
        }
        elev_set_button_lamp(BUTTON_COMMAND,i,0);
    }
}


void update_lights(elev_button_type_t button, int floor, int value){
    elev_set_button_lamp(button, floor, value);
}


void floor_light_set() {            //set floor light
    int floor = get_elev_floor();                
    
    if(floor!=-1){
        elev_set_floor_indicator(floor);      //to keep the program from crashing
    }
}

int get_order(elev_button_type_t button, int floor){
    return elev_get_button_signal(button, floor);
}


void set_stoplight(int value){
    elev_set_stop_lamp(value);
}

int get_floor_signal(){
    if (elev_get_floor_sensor_signal() != -1){
        return elev_get_floor_sensor_signal();
    }
    return -1;
}