#include "elevator.h"
#include <stdio.h>

static Elevator m_elevator;


int elevator_init_hardware(void) {
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 0;
    }
    printf("Press STOP button to stop elevator and exit program.\n");
    return 1;
}

void elevator_init(void) {
    elevator_set_direction(DIRN_DOWN);
    int floor = elev_get_floor_sensor_signal();
    while (floor == -1) {
        floor = elev_get_floor_sensor_signal();
    }
    elevator_set_floor();
    elevator_set_direction(DIRN_STOP);
}

int elevator_check_valid_floor(void) {
    return (elev_get_floor_sensor_signal() != -1);
}

void elevator_set_floor(void) {
    if (elev_get_floor_sensor_signal() != -1) {
        m_elevator.floor = elev_get_floor_sensor_signal();
        light_set_floor_indicator();
    }
}

int elevator_get_floor(void) {
    return m_elevator.floor;
}

float elevator_get_floor_in_between(void) {     // Used in emergencies when stopped between floors.
    if (elevator_get_previous_direction() == DIRN_UP) {
        return (elevator_get_floor() + 0.5);
    } 
    else if (elevator_get_previous_direction() == DIRN_DOWN) {
        return (elevator_get_floor() - 0.5);
    } 
    else {
        return (float)elevator_get_floor();
    }
}

void elevator_set_direction(elev_motor_direction_t dir) {
    if (m_elevator.dir == -dir && elevator_check_valid_floor()) {
         elev_set_motor_direction(dir);
    }
    else if (m_elevator.dir == DIRN_STOP) {
        elev_set_motor_direction(dir);
    } 
    else if (dir == DIRN_STOP) {
        elev_set_motor_direction(dir);
    }

    m_elevator.dir = dir;
    if (m_elevator.dir != DIRN_STOP && elevator_check_valid_floor()) {  // dir_previous registers direction before stop, otherwise the same as dir.
        m_elevator.dir_previous = m_elevator.dir;
    }
}

elev_motor_direction_t elevator_get_direction(void) {
    return m_elevator.dir;
}

elev_motor_direction_t elevator_get_previous_direction(void) {
    return m_elevator.dir_previous;
}

int elevator_emergency(void) {
    return elev_get_stop_signal();
}

void elevator_emergency_stop(void) {
    elevator_set_direction(DIRN_STOP);
    for (int i = 0; i < N_ORDER_TAGS; i++){
        queue_pop(i);
    }
}
