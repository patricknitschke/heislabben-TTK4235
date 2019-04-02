#include "elev.h"
#include <stdio.h>
#include "elevator.h"


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_DOWN);
    start();

    int first = -1;
    while(first == -1){ 
        first = listen();
    }
    set_target(first);




    

    

        //Nå funker listen, men må fikse get_button
    

    


    while (1) {
        // Change direction when we reach top/bottom floor
        
        //set_elevator();
        first = listen();
        if (first != -1) {
            set_target(first);
        }
        stop_n_kill_button();
        

       
       
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
            getElevator()->dir = DIRN_DOWN;

        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
            getElevator()->dir = DIRN_UP;
        }
        

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    return 0;
}
