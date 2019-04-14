#include "door.h"

static Door m_door;

void door_init(void) {
    m_door.door_timer[START_TIMER] = 0;
    m_door.door_timer[TIMER_ENABLED] = 0;
    m_door.door_is_open = 0;
}

void door_enable_timer(void) {
    if (!m_door.door_timer[TIMER_ENABLED]) { 
        m_door.door_timer[START_TIMER] = clock();
        m_door.door_timer[TIMER_ENABLED] = 1;
    }
}

void door_reset_timer(void) {
    m_door.door_timer[TIMER_ENABLED] = 0;
}

void door_open(void) {
    elevator_set_direction(DIRN_STOP);
    door_enable_timer();
    elev_set_door_open_lamp(1);
    m_door.door_is_open = 1;
}

void door_close(void) {
    door_reset_timer();
    elev_set_door_open_lamp(0);
    m_door.door_is_open = 0;
}

int door_check_open(void) {
    return m_door.door_is_open;
}

int door_check_timer(void) {
    return (clock() - m_door.door_timer[START_TIMER] > 3*CLOCKS_PER_SEC);
}

int door_picked_up(void) {
    return door_check_timer();
}
