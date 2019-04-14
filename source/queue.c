#include "queue.h"
#include <stdio.h>

static Queue m_queue;


void queue_init(void) {
    for (int i = 0; i < N_ORDER_TAGS; i++) {
        queue_pop(i);
    }
    m_queue.target_floor = elevator_get_floor();
}

void queue_set_target_floor(int target) {
    m_queue.target_floor = target;
}

void queue_set(int floor_order) {
    m_queue.queue[floor_order] = 1;
}

void queue_pop(int floor_order) {
    m_queue.queue[floor_order] = 0;
}

int queue_count(void) {
    int count = 0;
    for (int i = 0; i < N_ORDER_TAGS; i++) {
        if (m_queue.queue[i]) {
            count += 1;
        }
    }
    return count;
}

int queue_get_order(elev_button_type_t button, int floor) {
    return elev_get_button_signal(button, floor);
}

int queue_check_order_above_floor(int floor) {
    for (int i = 2*floor+1; i < N_ORDER_TAGS; i++) { // Start checking above floor
        if (m_queue.queue[i] == 1) {
            return 1;
        }
    }
    return 0;
}

int queue_check_order_below_floor(int floor) {
        for (int i = 2*(floor-1); i > -1; i--) { // Start checking below floor
        if (m_queue.queue[i] == 1) {
            return 1;
        }
    }
    return 0;
}

void queue_clear_orders_at_floor(int floor) {
    queue_pop(2*floor);
    queue_pop(2*floor-1);
    light_shut_at_floor(floor);
}

void queue_check_buttons_inside(void) {
    for (int i = 0; i < N_FLOORS; i++) {
        if (queue_get_order(BUTTON_COMMAND, i)) {
            if (i != N_FLOORS-1) {
                queue_set(2*i);
            }
            if (i != 0) {
                queue_set(2*i-1);
            }
            light_set_lamp(BUTTON_COMMAND, i, 1);
        }
    }
}

void queue_check_buttons_outside(void) {
    for (int i = 0; i < N_FLOORS; i++) {
        if (i != N_FLOORS-1) {
            if (queue_get_order(BUTTON_CALL_UP, i)) {
                queue_set(2*i);
                light_set_lamp(BUTTON_CALL_UP, i, 1);
            }
        }        
        if (i != 0) {
            if (queue_get_order(BUTTON_CALL_DOWN, i)) {
                queue_set(2*i-1);
                light_set_lamp(BUTTON_CALL_DOWN, i, 1);
            }
        }
    }
}

void queue_listen_and_find(void) {
    queue_check_buttons_inside();
    queue_check_buttons_outside();
    queue_find_target();
}

void queue_find_target(void) {
    int min = N_FLOORS-1;   // Aims to find a target furthest away
    int max = 0;
    int check_up_order = 0;
    int check_down_order = 0;
    for (int i = 0; i < N_FLOORS; i++) {
        if (m_queue.queue[2*i] == 1 && i != N_FLOORS -1) {  // Check up orders
            check_up_order = 1;
            max = i;
            if (i < min) {
                min = i;
            }
        }
        if (m_queue.queue[2*i-1] == 1 && i != 0) {  // Check down orders
            check_down_order = 1;
            if (i < min){
                min = i;
            }
            max = i;
        }
    }
    if (queue_count() == 1) {   // If queue_count == 1, max == min.
        if (check_up_order) {
            queue_set_target_floor(max);
        }
        else if (check_down_order) {
            queue_set_target_floor(min);
        }
    }
    else if (elevator_get_previous_direction() == DIRN_UP) {    // Furthest target above
        queue_set_target_floor(max);
    }
    else if (elevator_get_previous_direction() == DIRN_DOWN) {  // Furthest target below
        queue_set_target_floor(min);
    }
    else {
        queue_set_target_floor(elevator_get_floor());
    }
}

void queue_chase_target(void) {
    int target_floor = m_queue.target_floor;
    float current_floor = (float)elevator_get_floor();  // Float used to distinguish legitimate and in between floors. Used in emergency when elevator is in between floors.
    
    if (!elevator_check_valid_floor()) {
        current_floor = elevator_get_floor_in_between();  // current_floor is basically get_elev_floor() ± 0.5 depending on previous direction
    }
    if (current_floor > target_floor) {     // If above target, go down
        elevator_set_direction(DIRN_DOWN);
    }
    else if (current_floor < target_floor) {    // If below target, go up
        elevator_set_direction(DIRN_UP);
    }
    else {
        elevator_set_direction(DIRN_STOP);
    }
}

int queue_stop_n_serve_order(void) {
    int current_floor = elevator_get_floor();
    if (elevator_check_valid_floor()) {
        if (current_floor == N_FLOORS-1) {
            elevator_set_direction(DIRN_DOWN);
        }
        if (current_floor == 0) {
            elevator_set_direction(DIRN_UP);
        }       

        /* Serves the customer if:
            1. Direction is up and same direction order
            2. Direction is up and no orders above
            3. Direction is down and same direction order
            4. Direction is down and no orders below
            5. Last order in queue
        */
        int up_order_at_floor = m_queue.queue[2*current_floor];
        int down_order_at_floor = m_queue.queue[2*current_floor-1];
        
        if ((elevator_get_previous_direction() == DIRN_UP
            && (up_order_at_floor == 1 || (queue_check_order_above_floor(current_floor) == 0 && down_order_at_floor == 1)))
            || (elevator_get_previous_direction() == DIRN_DOWN 
            && (down_order_at_floor == 1 || (queue_check_order_below_floor(current_floor) == 0 && up_order_at_floor == 1)))
            || queue_count() == 0) {
            
            queue_clear_orders_at_floor(current_floor);
            return 1;
        }
    }
    return 0;
}