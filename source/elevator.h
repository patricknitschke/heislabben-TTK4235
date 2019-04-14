/** @file
*@brief This file contains the elevator module and its functions.
*
*/

#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "elev.h"
#include "queue.h"
#include "lights.h"
#include "door.h"


/**
*@brief A struct that holds information regarding the elevators position and direction.
*
*@param floor Current or last registered floor of the elevator.
*@param dir Current direction of the elevator.
*@param dir_previous Remembers the previous direction of the elevator before it stops.
*/
typedef struct Elevator {
    int floor;
    elev_motor_direction_t dir;
    elev_motor_direction_t dir_previous;
} Elevator;


/**
*@brief Initialises the elevator hardware.
*
*@return 1 on successful initialisation, 0 if it fails.
*/
int elevator_init_hardware(void);


// Start downwards, stop at defined state.
int elevator_init(void);


// Returns true if elevator is on a floor.
int elevator_check_valid_floor(void);


// Updates elevator floor to current floor, if legitimate.
void elevator_set_floor(void);


// Returns last visited floor.
int elevator_get_floor(void);


// Returns the last visited floor ± 0.5, depending on the previous direction.
float elevator_get_floor_in_between(void);


/**
*@brief Sets both elevator direction and motor direction to the same direction.
*
*@param[in] dir Direction to set the motor and @p m_elevator.dir to.
*/
void elevator_set_direction(elev_motor_direction_t dir);


// Returns the elevator direction.
elev_motor_direction_t elevator_get_direction(void);


// Returns the last recorded elevator direction, before the elevator stops.
elev_motor_direction_t elevator_get_previous_direction(void);


// Returns true if stop button pressed.
int elevator_emergency(void);


// Stops motor and emptys current queue if stop button pressed.
void elevator_emergency_stop(void);

#endif