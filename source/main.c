#include "elev.h"
#include "elevator.h"
#include "states.h"
#include "time.h"



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
    time_t timer= 0;


    while (current_state != END_STATE) {
        timer = clock();
        /*  Write code that needs to be checked regardless of state here  */
        
        // Handling stop button pressed according to standards specified.
        if(elev_get_stop_signal()){
            current_state = EMERGENCY;
        }

        // Stop elevator and exit program if the obstruction switch is flipped.
        if (elev_get_obstruction_signal()) {
            current_state = END_STATE;
        }
        

        /* Runs the state machine through switch case. */
        switch(current_state) {
            case START: // Sets up elevator and moves to a defined state.
                set_elev_direction(DIRN_DOWN);
                start();

                current_state = IDLE;
                break;


            case IDLE: // Do nothing while waiting for queue order.
                set_elev_direction(DIRN_STOP);
                if (listen() != -1) { 
                    set_target();
                    current_state = DRIVING;
                }
                break;


            case DRIVING: // Main state for most of the time
                listen(); // Checks for other orders while driving
                set_target();
                set_elev_floor(); 
                stop_n_kill_button(); // Picks up hitchhikers and updates queue.
                 //If empty queue, transition to IDLE
                if (queue_count() == 0 ) {
                    current_state = IDLE;
                }
                break;


            case EMERGENCY:
                emergency_stop();
                while(elev_get_stop_signal());
                continue_driving();
                current_state = DRIVING;
                break;               


            case END: // Stops the state machine
                set_elev_direction(DIRN_STOP);
                break;
        }
    }

    return 0;
}
