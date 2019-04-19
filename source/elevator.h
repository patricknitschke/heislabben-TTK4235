/** @file
*@brief %Elevator module and its corresponding functions.
*
*This file contains the elevator struct and includes functions that update the struct and
*control the motion of the elevator.
*/
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "elev.h"
#include "queue.h"
#include "lights.h"
#include "door.h"


/**
*@brief A struct that holds information regarding the elevator's position and direction.
*
*@param floor Current or last registered floor of the elevator.
*@param dir Current direction of the elevator.
*@param dir_previous Remembers the previous direction of the elevator before it stops.
*
*@note dir_previous is never set to DIRN_STOP.
*/
typedef struct Elevator {
    int floor;
    elev_motor_direction_t dir;
    elev_motor_direction_t dir_previous;
} Elevator;


/**
*@brief Initialises the elevator hardware.
*
*Calls upon ::elev_init to initialise elevator.
*
*@return 1 on successful initialisation, 0 if it fails.
*/
int elevator_init_hardware(void);


/**
*@brief Initialises the elevator variables and moves the elevator downwards
*until it reaches a defined state.
*
*@p floor is set to the current floor. @n
*@p dir is set to DIRN_STOP. @n
*@p dir_previous is set to DIRN_DOWN.
*/
void elevator_init(void);


/**
*@brief Used to check if the elevator is on a floor.
*
*@return 1 if the elevator is on a floor, 0 otherwise.
*/
int elevator_check_valid_floor(void);


/**
*@brief Uses the elevator floor sensor to set the elevator floor variable, @p floor, to the current floor.
*
*@p floor is only set when the elevator is on a valid floor.
*/
void elevator_set_floor(void);


/**
*@brief Gets the elevator floor variable.
*
*@return Elevator's current or last visited floor, @p floor.
*/
int elevator_get_floor(void);


/**
*@brief Gets the elevator floor variable and adds ± 0.5, depending on the elevator's
*previous direction.
*
*@return @p floor + 0.5, when @p dir_previous is DIRN_UP.@n
*@p floor - 0.5, when @p dir_previous is DIRN_DOWN.
*
*This is useful in case of emergencies when the elevator is stopped in between floors and needs
*to serve an order that was at its previous floor.
*/
float elevator_get_floor_in_between(void);


/**
*@brief Sets both elevator direction and motor direction to the same direction.
*
*@param[in] dir Direction to set the motor and elevator variable, @p dir to.
*
*@p dir_previous will mirror @p dir unless @p dir is DIRN_STOP. This will allow @p dir_previous
*to remember the previous direction in case the elevator stops.
*
*/
void elevator_set_direction(elev_motor_direction_t dir);


/**
*@brief Gets the elevator's current direction, @p dir.
*
*@return Current elevator direction, @p dir.
*/
elev_motor_direction_t elevator_get_direction(void);


/**
*@brief Gets the elevator's previous direction, @p dir_previous.
*
*@return Previous elevator direction, @p dir_previous.
*/
elev_motor_direction_t elevator_get_previous_direction(void);


/**
*@brief Checks for an emergency through the stop button status.
*
*@return 1 if stop button pressed, 0 otherwise.
*/
int elevator_emergency(void);


/**
*@brief  Stops the elevator, sets @p dir to DIRN_STOP and empties the queue.
*
*/
void elevator_emergency_stop(void);

#endif