#include "queue.h"
#include <unistd.h>
#include <stdio.h>

static Queue m_queue;


void init_queue(void) {
    for (int i = 0; i < N_ORDER_TAGS; i++) {
        pop_queue(i);
    }
}

void set_target_floor(int target) {
    m_queue.target_floor = target;
}

void set_queue(int floor_order) {
    m_queue.queue[floor_order] = 1;
}

void pop_queue(int floor_order) {
    m_queue.queue[floor_order] = 0;
}

void clear_orders_at_floor(int floor) {
    clear_lights_at_floor(floor);
    pop_queue(2*floor);
    pop_queue(2*floor-1);
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

int check_order_above_floor(int floor) {
    for (int i = 2*floor+1; i < N_ORDER_TAGS; i++) { // Start checking above floor
        if (m_queue.queue[i] == 1) {
            return 1;
        }
    }
    return 0;
}

int check_order_below_floor(int floor) {
        for (int i = 2*(floor-1); i > -1; i--) { // Start checking below floor
        if (m_queue.queue[i] == 1) {
            return 1;
        }
    }
    return 0;
}

void check_buttons_inside(void) {
    for (int i = 0; i < N_FLOORS; i++) {
        if (elev_get_button_signal(BUTTON_COMMAND, i)) {
            if (i != N_FLOORS-1) {
                set_queue(2*i);
            }
            if (i != 0) {
                set_queue(2*i-1);
            }
            elev_set_button_lamp(BUTTON_COMMAND, i, 1);
        }
    }
}

void check_buttons_outside(void) {
    for (int i = 0; i < N_FLOORS; i++) {
        if (i != N_FLOORS-1) {
            if (elev_get_button_signal(BUTTON_CALL_UP, i)) {
                set_queue(2*i);
                elev_set_button_lamp(BUTTON_CALL_UP, i, 1);
            }
        }        
        if (i != 0) {
            if (elev_get_button_signal(BUTTON_CALL_DOWN,i)) {
                set_queue(2*i-1);
                elev_set_button_lamp(BUTTON_CALL_DOWN,i,1);
            }
        }
    }
}

void listen_and_find(void) {
    check_buttons_inside();
    check_buttons_outside();
    find_target();
}

void find_target(void) {
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
            set_target_floor(max);
        }
        else if (check_down_order) {
            set_target_floor(min);
        }
    }
    else if (get_elev_previous_direction() == DIRN_UP) {    // Furthest target above
        set_target_floor(max);
    }
    else if (get_elev_previous_direction() == DIRN_DOWN) {  // Furthest target below
        set_target_floor(min);
    }
    else {
        set_target_floor(get_elev_floor());
    }
}

void chase_target(void) {
    int target_floor = m_queue.target_floor;
    printf("Target: %dnd floor.\n", target_floor);
    printf("Current direction: %d.\n", get_elev_direction());
    printf("Previous direction: %d.\n", get_elev_previous_direction());

    float current_floor = (float)get_elev_floor();  // Float used to distinguish legitimate and in between floors. Used in case of emergency and elevator in between floors.
    if (!check_valid_floor()) {
        current_floor = get_elev_floor_in_between();  // current_floor basically is get_elev_floor() ± 0.5 depending on previous direction
    }
    if (current_floor > target_floor) {     // If above target, go down
        set_elev_direction(DIRN_DOWN);
    }
    else if (current_floor < target_floor) {    // If below target, go up
        set_elev_direction(DIRN_UP);
    }
    else {
        set_elev_direction(DIRN_STOP);
    }
}

int stop_n_kill_button(void) {
    int current_floor = get_elev_floor();
    if(elev_get_floor_sensor_signal() != -1){
        if (current_floor == N_FLOORS-1) {
            set_elev_direction(DIRN_DOWN);
        }
        if (current_floor == 0) {
            set_elev_direction(DIRN_UP);
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

        if ((get_elev_previous_direction() == DIRN_UP
            && (up_order_at_floor == 1 || (check_order_above_floor(current_floor) == 0 && down_order_at_floor == 1)))
            || (get_elev_previous_direction() == DIRN_DOWN 
            && (down_order_at_floor == 1 || (check_order_below_floor(current_floor) == 0 && up_order_at_floor == 1)))
            || queue_count() == 0) {

            clear_orders_at_floor(current_floor);
            return 1;
        }
    }
    return 0;
}