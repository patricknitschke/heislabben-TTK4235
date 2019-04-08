#include "queue.h"
#include <unistd.h>
#include <time.h>

Queue m_queue;

int timer;
//sett inn et element i queue
void set_queue(int floor_order){
    m_queue.queue[floor_order] = 1;
}

//returner listen (queue)
struct Queue* get_queue(){
    return &m_queue;
}

//ta ut når ekspedert
void pop_queue(int floor_order) {
    m_queue.queue[floor_order] = 0;
}


//finn ut om noen trykker på heiskallknapp, sett dette inn i queue
int listen(void) {
    check_buttons_inside();
    for (int i = 0; i <= 3; i++) {

        if(i!=3){
            if (elev_get_button_signal(BUTTON_CALL_UP,  i)) {
            set_queue(2*i);
            elev_set_button_lamp(BUTTON_CALL_UP, i, 1);
            return (2*i);
            }
        }        
    
        if (i!=0 ) {
            if (elev_get_button_signal(BUTTON_CALL_DOWN,i)) {
            set_queue(2*i-1);
            elev_set_button_lamp(BUTTON_CALL_DOWN,i,1);
            return (2*i-1);
            }
        }
       
        
    }
    return (-1);
}


//sett målet for hvor heisen skal i en gitt retning. kaller noen på heisen forbi, sett målet her.
void chase_target(){
    int target_floor = find_target();
    //printf(target_floor);

    if (get_elev_floor() > target_floor){
        set_elev_direction(DIRN_DOWN);
    }
    
    else if (get_elev_floor() < target_floor){
        set_elev_direction(DIRN_UP);
    }
    else{
        if(get_elev_direction() == DIRN_UP){
            set_elev_direction(DIRN_DOWN);
        }
        else{
            set_elev_direction(DIRN_UP);
        }
    }
}

int find_target(){
    int min = 3;
    int max = 0;
    
    bool dir_up = false;
    bool dir_down = false;

    for (int i = 0; i <= 3; i++) {
        if (m_queue.queue[2*i-1] == 1) {  // Check down orders
            dir_down = true;
            if(i<min){
                min = i;
            }
            max = i;
        }

        if (m_queue.queue[2*i] == 1) { // Check up orders
            dir_up = true;
            max = i;
            if(i<min){
                min = i;
            }
        }
    }

    if (queue_count() == 1){
        if (dir_up) {
            return max;
        }
        else if(dir_down) {
            return min;
        }
    }
    else if (get_elev_direction() == DIRN_DOWN){
        return min;
    }
    else if (get_elev_direction() == DIRN_UP){
        return max;
    }
    return (get_elev_floor());
}


//Hvis noen er på veien: Plukk de opp og skru av lyset når de er hentet.
void stop_n_kill_button(){
    set_elev_floor();
    int floor = get_elev_floor();
    int timer_clock = clock();

    if (floor == 3 ){
        set_elev_direction(DIRN_DOWN);
    }
    if (floor == 0){
        set_elev_direction(DIRN_UP);
    }

    for (int i = 0; i < 4; i++) {
        if (get_elev_direction() == DIRN_UP || queue_count() == 1) {
            if (floor == i && m_queue.queue[2*i]) {
                elev_set_button_lamp(BUTTON_CALL_UP,floor,0);
                elev_set_button_lamp(BUTTON_COMMAND,floor,0);
                if(i!=0){
                    elev_set_button_lamp(BUTTON_CALL_DOWN,floor,0);
                }
            pop_queue(2*i);
            pop_queue(2*i-1);
            station_stop(DIRN_UP , timer_clock);
            }
        }

        if (get_elev_direction() == DIRN_DOWN || queue_count() == 1) {
            if (floor == i && m_queue.queue[2*i-1]) {
                elev_set_button_lamp(BUTTON_CALL_DOWN,floor,0);
                elev_set_button_lamp(BUTTON_COMMAND,floor,0);
                if(i!=3){
                    elev_set_button_lamp(BUTTON_CALL_UP,floor,0);
                }
            pop_queue(2*i-1);
            pop_queue(2*i);
            station_stop(DIRN_DOWN, timer_clock);
            }
        }
    }
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






