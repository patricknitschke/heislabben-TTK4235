#include "door.h"

static Door m_door;

void enable_timer(void) {
    if (!m_door.door_timer[TIMER_ENABLED]) { 
        m_door.door_timer[START_TIMER] = clock();
        m_door.door_timer[TIMER_ENABLED] = 1;
    }
}

void reset_timer() {
    m_door.door_timer[TIMER_ENABLED] = 0;
}

void open_door() {
    set_elev_direction(DIRN_STOP);
    enable_timer();
    elev_set_door_open_lamp(1);
    m_door.door_is_open = 1;
}

void close_door() {
    reset_timer();
    elev_set_door_open_lamp(0);
    m_door.door_is_open = 0;
}

int check_door_open() {
    return m_door.door_is_open;
}

int check_timer() {
    return (clock() - m_door.door_timer[START_TIMER] > 3*CLOCKS_PER_SEC);
}

int picked_up() {
    return check_timer();
}
