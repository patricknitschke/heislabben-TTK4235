#include "elevator.h"
#include "lights.h"
#include "door.h"
#include <unistd.h>
#include <stdio.h>

static Elevator m_elevator;

// Start downwards, stop at defined state
int init_elevator(void) {
    set_elev_direction(DIRN_DOWN);
    int floor = elev_get_floor_sensor_signal();
    while (floor == -1) {
        floor = elev_get_floor_sensor_signal();
    }
    set_elev_floor();
    set_elev_direction(DIRN_STOP);
    return floor;
}

int check_valid_floor(void) {
    return (elev_get_floor_sensor_signal() != -1);
}

void set_elev_floor(void) {
    if (elev_get_floor_sensor_signal() != -1) {
        m_elevator.floor = elev_get_floor_sensor_signal();
        floor_light_set();
    }
}

int get_elev_floor(void) {
    return m_elevator.floor;
}

float get_elev_floor_in_between(void) {
    if (get_elev_previous_direction() == DIRN_UP) {
        return (get_elev_floor() + 0.5);
    } 
    else if (get_elev_previous_direction() == DIRN_DOWN) {
        return (get_elev_floor() - 0.5);
    } 
    else {
        return (float)get_elev_floor();
    }
}

void set_elev_direction(elev_motor_direction_t dir) {
    if (m_elevator.dir == -dir && check_valid_floor()) {
         elev_set_motor_direction(dir);
    }
    else if (m_elevator.dir == DIRN_STOP) {
        elev_set_motor_direction(dir);
    } 
    else if (dir == DIRN_STOP) {
        elev_set_motor_direction(dir);
    }

    m_elevator.dir = dir;
    if (m_elevator.dir != DIRN_STOP && check_valid_floor()) {
        m_elevator.dir_previous = m_elevator.dir;
    }
}

elev_motor_direction_t get_elev_direction(void) {
    return m_elevator.dir;
}

elev_motor_direction_t get_elev_previous_direction(void) {
    return m_elevator.dir_previous;
}

int emergency(void) {
    return elev_get_stop_signal();
}

void elevator_emergency_stop(void) {
    set_elev_direction(DIRN_STOP);
    for (int i = 0; i < N_ORDER_TAGS; i++){
        pop_queue(i);
    }
}
