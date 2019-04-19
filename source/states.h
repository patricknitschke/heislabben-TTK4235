/** @file
*@brief State definitions and its corresponding functions.
*
*This file contains the necessary states to implement a functioning elevator.
*/
#ifndef STATES_H
#define STATES_H
#include "elevator.h"
#include "queue.h"
#include "lights.h"
#include "door.h"


/**
*@enum tag_state
*State tags used in the finite state machine (FSM). These brief descriptions are elaborated further in
*their respective state functions.
*
*@var START
*State where the initialisation of the elevator occurs.
*
*@var IDLE
*State where the elevator idles whilst waiting for an order.
*
*@var DRIVING
*State where the elevator is in motion, attempting to reach a target.
*
*@var PICKUP
*State when the elevator stops to serve a customer and doors are controlled.
*
*@var EMERGENCY
*State when the stop button is pressed and handled according to specific standards.
*
*@var END
*State which signifies that the FSM stops.
*/
typedef enum tag_state {
	START, IDLE, DRIVING, PICKUP, EMERGENCY, END
} state;


/**
*@brief Transitions the FSM to an emergency state if the stop button pressed.
*
*@param[in] current_state State that FSM currently is in. Used to maintain state.
*@returns EMERGENCY state if the stop button is pressed, @p current_state if not.
*/
state state_pending_emergency(state current_state);


/* STATE DEFINITIONS BELOW */

/**
*@brief Initialises elevator, queue and door modules.
*
*Runs the initialisation functions for the elevator, queue and door modules.
*
*@returns IDLE on successful initialisation. END if hardware initialisation fails.
*@sa ::elevator_init_hardware, ::elevator_init, ::queue_init and ::door_init 
*for more details.
*/
state state_start(void);


/**
*@brief Does nothing. Stays in IDLE if the queue is empty, transition to DRIVING otherwise.
*
*@returns DRIVING if the queue is not empty, i.e. an order is pending. Otherwise, returns IDLE.
*/
state state_idle(void);


/**
*@brief Continuously drives towards the elevator target.
*
*The elevator's floor and direction is continuously set to reach a defined target.
*Once a target is reached or there is an order in the same direction, the FSM
*transitions to PICKUP.
*
*@returns PICKUP on reaching a floor with an appropriate order. Otherwise, returns DRIVING.
*@sa ::queue_stop_n_serve_order for details on what is an appropriate order.
*/
state state_driving(void);


/**
*@brief Controls the door using a timer.
*
*Stops the motor and starts a timer of 3 seconds. Once the customer has entered (after 3 seconds),
*the FSM will transition to IDLE if there are no other orders, or DRIVING if there are.
*
*@returns PICKUP while the timer is ongoing. Otherwise, IDLE if the queue is empty or DRIVING if not.
*/
state state_pickup(void);


/**
*@brief Stops the motor and empties the queue. %Elevator waits until emergency over.
*
*All queue orders are removed and all lights are turned off. Also, if on a valid floor,
*the doors are opened. Then, the elevator will stay in a 'busy' wait as long as the stop 
*button is pressed.
*
*@returns PICKUP when the elevator is on a valid floor. IDLE otherwise.
*@note If the doors are open, the doors remain open until after 3 seconds have passed.
*/
state state_emergency(void);


/**
*@brief Exits the FSM.
*
*The criteria in the while loop that runs the FSM fails, thus exiting the FSM. See main.c.
*
*@returns END.
*/
state state_end(void);


#endif