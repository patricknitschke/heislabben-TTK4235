#include "states.h"

state state_pending_emergency(state current_state) {
    if (elevator_emergency()) {
        return EMERGENCY;
    }
    else {
        return current_state;
    }
}

/* State definitions below */

state state_start(void) {
    if (!elevator_init_hardware()) {
        return END;
    }
	elevator_init();
	queue_init();
    door_init();
    return IDLE;
}

state state_idle(void) {
    if (queue_count() != 0) { 
        return DRIVING;
    }
    else {
        return IDLE;
    }
}

state state_driving(void) {
    elevator_set_floor();
    int found_a_customer = queue_stop_n_serve_order();
    
    queue_chase_target();
    if (found_a_customer) { // As we find a customer, transition to PICKUP
        return PICKUP;
    }
    else {
        return DRIVING;
    }
}

state state_pickup(void) {
    door_open(); //Stops motor and starts timer
    
    if (door_picked_up()) {
    	door_close();

        if (queue_count() == 0 ) {  // If empty queue, transition to IDLE
            return IDLE;
        }
        else {
             return DRIVING;
        }
    }
    else {
        return PICKUP;
    }
}

state state_emergency(void) {
    elevator_emergency_stop();
    light_shut_all();
    light_set_stop_lamp(1);
    if (elevator_check_valid_floor()) {
        door_open();
    }

    while(elevator_emergency()); // Handling stop button pressed according to standards specified
    light_set_stop_lamp(0);
    
    if (door_check_open()) {
        door_reset_timer();
        return PICKUP;
    } 
    else {
        return IDLE;
    }
}

state state_end(void) {
	return END;
}
