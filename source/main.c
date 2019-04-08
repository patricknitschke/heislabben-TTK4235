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
    int timer_enabled = 0;
    int timer_completed = 0;
    int start_timer = 0;
    int current_timer = 0;


    /* Main loop that runs the elevator */
    while (current_state != END_STATE) {
        /*  Write code that needs to be checked regardless of state here  */
        current_timer = clock();
        
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
                elev_set_motor_direction(DIRN_STOP);
                //set_elev_direction(DIRN_STOP);
                listen();
                if (queue_count() != 0) { 
                    current_state = DRIVING;
                }
                break;


            case DRIVING: // Main state for most of the time
                listen(); 
                set_elev_floor(); 

                // As we pick up hitchhiker, transition to PICKUP
                if(stop_n_kill_button() == 1) {
                    current_state = PICKUP;
                }

                if(queue_count()!=0){     
                    chase_target();// Checks for other orders while driving
                }

               
                break;
            

            case PICKUP: //when picking up
                set_elev_direction(DIRN_STOP);
                listen();
                if (!timer_enabled) {
                    start_timer = clock();
                    elev_set_door_open_lamp(1);
                    timer_enabled = 1;
                }
                timer_completed = pickup(start_timer, current_timer);

                if (timer_completed) {
                    if (queue_count() == 0 ) {
                        current_state = IDLE;
                    }
                    else{
                        current_state = DRIVING;
                    }
                    timer_enabled = 0;
                    elev_set_door_open_lamp(0);
                }
                 // If empty queue, transition to IDLE
            
                break;

            

            case EMERGENCY:
                emergency_stop();
                while(elev_get_stop_signal());
                set_elev_direction(DIRN_DOWN);
                start();
                current_state = IDLE;
                break;               


            case END: // Stops the state machine
                set_elev_direction(DIRN_STOP);
                break;
        }
    }

    return 0;
}
