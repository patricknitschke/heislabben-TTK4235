#include "queue.h"
#include <unistd.h>

struct Queue m_queue;

//sett inn et element i queue
void set_queue(int floor){
    m_queue.queue[floor] = 1;
}

//returner listen (queue)
struct Queue* get_queue(){
    return &m_queue;
}

//ta ut når ekspedert
void pop_queue(int floor) {
    m_queue.queue[floor] = 0;
}


//finn ut om noen trykker på heiskallknapp, sett dette inn i queue
int listen(void) {
    for (int i = 0; i <= 3; i++) {

        if(i!= 3){
            if (elev_get_button_signal(BUTTON_CALL_UP,  i)) {
            set_queue(2*i);
            elev_set_button_lamp(BUTTON_CALL_UP, i, 1);
            return (i);
            }
        }        
    
        if (i != 0) {
            if (elev_get_button_signal(BUTTON_CALL_DOWN,i)) {
            set_queue(2*i+1);
            elev_set_button_lamp(BUTTON_CALL_DOWN,i,1);
            return (i);
            }
        }
        
    }
    return (-1);
    
}


//sett målet for hvor heisen skal i en gitt retning. kaller noen på heisen forbi, sett målet her.
void set_target(int floor){

    if (getElevator()->floor > floor){
        elev_set_motor_direction(DIRN_DOWN);
        getElevator()->dir = DIRN_DOWN;
    }
    else if (getElevator()->floor == floor){
        getElevator()->dir = DIRN_STOP;
        //sleep(3);
    }
    else{
        elev_set_motor_direction(DIRN_UP);
        getElevator()->dir = DIRN_UP;
    }
}


//Hvis noen er på veien: Plukk de opp og skru av lyset når de er hentet.
void stop_n_kill_button(){
    int floor = elev_get_floor_sensor_signal();
    getElevator()->floor = floor;
    if(floor == 3){
        getElevator()->dir = DIRN_DOWN;
    }
    if(floor == 0){
        getElevator()->dir = DIRN_UP;
    }

    for (int i = 0; i < 4; i++) {
        if (getElevator()->dir == DIRN_UP) {
            if (floor == i && m_queue.queue[2*i]) {
            elev_set_button_lamp(BUTTON_CALL_UP,floor,0);
            pop_queue(2*i);
            station_stop(DIRN_UP);
            }
        }

        if (getElevator()->dir == DIRN_DOWN) {
            if (floor == i && m_queue.queue[2*i+1]) {
            elev_set_button_lamp(BUTTON_CALL_DOWN,floor,0);
            pop_queue(2*i+1);
            station_stop(DIRN_DOWN);
            }
        }
    }
}

//sjekk om køen er tom
bool check_empty_queue(){
    bool empty = 1;
    for (int i = 0; i<6; i++){
        if (m_queue.queue[i]){
            empty = false;
        }
    }
    return empty;
}





