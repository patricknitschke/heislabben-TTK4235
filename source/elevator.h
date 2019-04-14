#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "elev.h"
#include "queue.h"
#include "lights.h"

// A struct that holds information regarding the elevators position and direction.
typedef struct Elevator {
    int floor;
    elev_motor_direction_t dir;
    elev_motor_direction_t dir_previous;
} Elevator;


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


// Sets both elevator direction and motor direction to the same direction.
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