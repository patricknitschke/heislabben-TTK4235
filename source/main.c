/** 
*@mainpage %Elevator lab in the subject Embedded Systems, TTK4235
*
*This site contains documentation for the code used to implement an elevator in Embedded Systems, TTK4235.@n
*Written by Eivind Heldal Stray and Patrick Nitschke, Spring 2019.
*
*@section section1 Files
*To view our code, see the <a href="files.html">File List</a> page.
*/
#include "states.h"
#include "elevator.h"
#include "queue.h"

#define START_STATE START
#define END_STATE END


int main() {
    /*  Declare variables needed for state machine  */
    state current_state = START_STATE;

    /* Main loop that runs the elevator */
    while (current_state != END_STATE) {

        /*  Write code that needs to be checked regardless of state here  */
        queue_listen_and_find();    // Continuously checks for orders and sets a target for elevator.
        current_state = state_pending_emergency(current_state); // Sends the FSM to emergency state if stop button is pressed.

        /* Runs the state machine through switch case. */
        switch(current_state) {
            case START: // Sets up elevator and queue, and moves to a defined state.
                current_state = state_start();
                break;

            case IDLE: // Do nothing while waiting for queue order.
                current_state = state_idle();
                break;

            case DRIVING: // Chases a target and transitions to PICKUP when elevator reaches a customer.
                current_state = state_driving();
                break;

            case PICKUP: // Controls the door
                current_state = state_pickup();
                break;

            case EMERGENCY: // Empty queue and shut off all lights. Opens door if on a valid floor.
                current_state = state_emergency();
                break;               

            case END: // Stops the state machine
                current_state = state_end();
                break;
        }
    }

    return 0;
}