#include "queue.h"
#include <unistd.h>
#include <time.h>
#include <stdio.h>

static Queue m_queue;

int timer;
//sett inn et element i queue
void set_queue(int floor_order){
    m_queue.queue[floor_order] = 1;
}

//ta ut når ekspedert
void pop_queue(int floor_order) {
    m_queue.queue[floor_order] = 0;
}


//finn ut om noen trykker på heiskallknapp, sett dette inn i queue
void listen(void) {
    check_buttons_inside();
    for (int i = 0; i <= 3; i++) {
        if(i!=3){
            if (elev_get_button_signal(BUTTON_CALL_UP,  i)) {
            set_queue(2*i);
            elev_set_button_lamp(BUTTON_CALL_UP, i, 1);
            }
        }        
        if (i!=0) {
            if (elev_get_button_signal(BUTTON_CALL_DOWN,i)) {
            set_queue(2*i-1);
            elev_set_button_lamp(BUTTON_CALL_DOWN,i,1);
            
            }
        }
    }
}

int check_order_above_floor(int floor) {
    for (int i = 2*floor+1; i < N_FLOOR_NAMES; i++) { //Start checking above floor
        if (m_queue.queue[i] == 1) {
            return 1;
        }
    }
    return 0;
}

int check_order_below_floor(int floor) {
        for (int i = 2*(floor-1); i > -1; i--) { //Start checking below floor
        if (m_queue.queue[i] == 1) {
            return 1;
        }
    }
    return 0;
}


//sett målet for hvor heisen skal i en gitt retning. kaller noen på heisen forbi, sett målet her.
void chase_target(){
    int target_floor = find_target();
    float current_floor = (float)get_elev_floor();

    if (!check_valid_floor()) {
        current_floor = get_elev_floor_in_between();
    }

    printf("Target: %d\n", target_floor);
    printf("Current: %f\n", current_floor);

    if (current_floor > target_floor){
        set_elev_direction(DIRN_DOWN);
    }
    else if (current_floor < target_floor){
        set_elev_direction(DIRN_UP);
    }
    else {
        if(get_elev_direction() == DIRN_UP && check_order_above_floor(current_floor) == 0){
            set_elev_direction(DIRN_DOWN);
        }
        else if (get_elev_direction() == DIRN_DOWN && check_order_below_floor(current_floor) == 0){
            set_elev_direction(DIRN_UP);
        }
    }
}

int find_target(){
    int min = N_FLOORS-1;
    int max = 0;
    
    int up_order = 0;
    int down_order = 0;

    for (int i = 0; i < 4; i++) {
        if (m_queue.queue[2*i] == 1 && i != N_FLOORS -1) { // Check up orders
            up_order = 1;
            max = i;
            if(i < min){
                min = i;
            }
        }

        if (m_queue.queue[2*i-1] == 1 && i != 0) {  // Check down orders
            down_order = 1;
            if(i < min){
                min = i;
            }
            max = i;
        }
    }

    if (queue_count() == 1) {
        if (up_order) {
            return max;
        }
        else if(down_order) {
            return min;
        }
    }
    else if (get_elev_previous_direction() == DIRN_UP){
        return max;
    }
    else if (get_elev_previous_direction() == DIRN_DOWN){
        return min;
    }
    return get_elev_floor();
}


//Hvis noen er på veien: Plukk de opp og skru av lyset når de er hentet.
int stop_n_kill_button(){
    int floor = get_elev_floor();
    if(elev_get_floor_sensor_signal() != -1){
        if (floor == 3) {
            set_elev_direction(DIRN_DOWN);
        }
        if (floor == 0) {
            set_elev_direction(DIRN_UP);
        }       
        for (int i = 0; i < 4; i++) {
            if (get_elev_direction() == DIRN_UP || queue_count() == 1) {
                int up_order = m_queue.queue[2*i];
                if (floor == i && up_order == 1 && i != N_FLOORS-1) {
                    elev_set_button_lamp(BUTTON_CALL_UP,floor,0);
                    elev_set_button_lamp(BUTTON_COMMAND,floor,0);
                    if(i != 0){
                        elev_set_button_lamp(BUTTON_CALL_DOWN,floor,0);
                    }
                    pop_queue(2*i);
                    pop_queue(2*i-1);
                    return 1;
                }
            }

            if (get_elev_direction() == DIRN_DOWN || queue_count() == 1) {
                int down_order = m_queue.queue[2*i-1];
                if (floor == i && down_order == 1 && i != 0) {
                    elev_set_button_lamp(BUTTON_CALL_DOWN,floor,0);
                    elev_set_button_lamp(BUTTON_COMMAND,floor,0);
                    if(i != 3){
                        elev_set_button_lamp(BUTTON_CALL_UP,floor,0);
                    }
                    pop_queue(2*i-1);
                    pop_queue(2*i);
                    return 1;
                }
            }
        }
    }
    return 0;
}

//sjekk om køen er tom
int queue_count(){
    int count = 0;
    for (int i = 0; i<6; i++){
        if (m_queue.queue[i]){
            count +=1;
        }
    }
    return count;
}



void check_buttons_inside(){
    for(int i = 0;i<4;i++){
        if(elev_get_button_signal(BUTTON_COMMAND, i)){
            if(i!=3){
                set_queue(2*i);
                
            }
            if(i!=0){
                set_queue(2*i-1);
            }
            elev_set_button_lamp(BUTTON_COMMAND, i, 1);

        }
    }
}






