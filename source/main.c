#include "elev.h"
#include "states.h"
#include "elevator.h"
#include "queue.h"
#include "lights.h"
#include "door.h"

#include <stdio.h>

#define START_STATE START
#define END_STATE END


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    printf("Press STOP button to stop elevator and exit program.\n");


    // Declare variables needed for state machine
    state current_state = START_STATE;

    /* Main loop that runs the elevator */
    while (current_state != END_STATE) {
        /*  Write code that needs to be checked regardless of state here  */
        
        queue_listen_and_find();
        current_state = state_pending_emergency(current_state);

        /* Runs the state machine through switch case. */
        switch(current_state) {
            case START: // Sets up elevator and queue, and moves to a defined state.
                current_state = state_start();
                break;

            case IDLE: // Do nothing while waiting for queue order.
                current_state = state_idle();
                break;

            case DRIVING: // Main state for most of the time
                current_state = state_driving();
                break;

            case PICKUP: // When picking up customer
                current_state = state_pickup();
                break;

            case EMERGENCY: // Empty queue and shut off all lights
                current_state = state_emergency();
                break;               

            case END: // Stops the state machine
                current_state = state_end();
                break;
        }
    }

    return 0;
}


/*
printf in chase target
printf in emergency state

press order same floor, 6 seconds. Because you press, but it registers 2 orders.
*/