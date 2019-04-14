#ifndef STATES_H
#define STATES_H
#include "elevator.h"
#include "queue.h"
#include "lights.h"
#include "door.h"

typedef enum state {
	START, IDLE, DRIVING, PICKUP, EMERGENCY, END
} state;


// Returns emergency state if stop button is pressed.
state state_pending_emergency(state current_state);


/* State definitions below */

// Initialises elevator and queue modules.
state state_start(void);


// Stays in IDLE as long as the queue is empty.
state state_idle(void);


// Continuously updates the elevator target based on the queue. Stops to pick up customers once we reach a floor with an order.
state state_driving(void);


// Controls the door using a timer.
state state_pickup(void);


// Stops motor and empties queue. Elevator waits until emergency over.
state state_emergency(void);


// Stops the motor and exits the FSM.
state state_end(void);


#endif