#include "elev.h"
#include "elevator.h"
#include "states.h"
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
        
        // Handling stop button pressed according to standards specified
        //Skriv en stop funksjon som tar inn current_state, gjør forskjellig ting avh. av state

        // Stop elevator and exit program if the obstruction switch is flipped.
        if (elev_get_obstruction_signal()) {
            current_state = END_STATE;
        }
        

        /* Runs the state machine through switch case. */
        switch(current_state) {
            case START: // Sets up elevator and moves to a defined state.
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
                if(elev_get_stop_signal() && elev_get_floor_sensor_signal()!=-1){
                    current_state = PICKUP;
                }
                
                break;


            case DRIVING: // Main state for most of the time
                listen(); 
                set_elev_floor(); 
                if(elev_get_stop_signal()){
                    current_state = EMERGENCY;
                }
                
                // As we find a customer, transition to PICKUP
                if(find_customer() == 1) {
                    current_state = PICKUP;
                }
                stop_n_kill_button();
                break;

            case PICKUP: //when picking up
                listen();
                open_door(); //Stops motor and starts timer

                if (picked_up()) {
                    if (queue_count() == 0 ) {  // If empty queue, transition to IDLE
                        current_state = IDLE;
                    }
                    else {
                        current_state = DRIVING;
                    }
                    close_door();
                }
                break;

            

            case EMERGENCY:
                emergency_stop();
                if(elev_get_stop_signal()){
                    set_stoplight(1);
                }
                while(elev_get_stop_signal());
                set_stoplight(0);
                kill_all_lights();
                current_state = IDLE;
                break;               


            case END: // Stops the state machine
                set_elev_direction(DIRN_STOP);
                break;
        }
    }

    return 0;
}
