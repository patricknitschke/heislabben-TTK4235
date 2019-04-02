#include "driver/elev.h"
#include <stdio.h>
#include "elevator.h"


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    set_elev_direction(DIRN_DOWN);
    start();

    int first = -1;
    while(first == -1){ 
        first = listen();
    }
    set_target(first);




    

    

        //Nå funker listen, men må fikse get_button
    

    


    while (1) {
        // Change direction when we reach top/bottom floor
        
        //handling stop button pressed according to standards specified.
        while(elev_get_stop_signal());

        int floor_order = listen();
        if(floor_order != -1){
            
            set_target();
            
            
        }

        set_elev_floor();
        
        stop_n_kill_button();

        

    /* 
       
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            set_elev_direction(DIRN_DOWN);

        } else if (elev_get_floor_sensor_signal() == 0) {
            set_elev_direction(DIRN_UP);
        }
        
*/
        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_obstruction_signal()) {
            set_elev_direction(DIRN_STOP);
            break;
        }
    }

    return 0;
}
