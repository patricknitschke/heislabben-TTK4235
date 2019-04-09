#include "door.h"

Door door;


int check_timer(){
    if(clock() - door.door_timer[START_TIMER] > 3*CLOCKS_PER_SEC) {
        return 1;
    } else {
        return 0;
    }
}

int picked_up() {
    if (check_timer()) { // Timer completed
        return 1;
    } else {
        return 0;
    }
}

void enable_timer() {
    if (!door.door_timer[TIMER_ENABLED]) { 
        door.door_timer[START_TIMER] = clock();
        door.door_timer[TIMER_ENABLED] = 1;
    }
}

void reset_timer() {
    door.door_timer[TIMER_ENABLED] = 0;
}

void open_door() {
    elev_set_motor_direction(DIRN_STOP);
    enable_timer();
    elev_set_door_open_lamp(1);
}

void close_door() {
    reset_timer();
    elev_set_door_open_lamp(0);
}

/*void remove_target(int target_floor) {
    if(target_floor != 3){
        update_lights(BUTTON_CALL_UP,target_floor,0);
        pop_queue(2*target_floor);
    }
    if (target_floor != 0) {
        update_lights(BUTTON_CALL_DOWN,target_floor,0);
        pop_queue(2*target_floor-1);
    }
    elev_set_button_lamp(BUTTON_COMMAND, target_floor,0);
}*/