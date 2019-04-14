#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "elev.h"
#include "channels.h"
#include "io.h"
#include "queue.h"
#include <time.h>
#include <stdbool.h>


// A struct that holds information regarding the elevators position and direction.
typedef struct Elevator {
    int floor;
    elev_motor_direction_t dir;
    elev_motor_direction_t dir_previous;
    int emergency_situation;
} Elevator;


// Start downwards, stop at defined state.
int init_elevator(void);


// Returns true if elevator is on a floor.
int check_valid_floor(void);


// Updates elevator floor to current floor, if legitimate.
void set_elev_floor(void);


// Returns last visited floor.
int get_elev_floor(void);


// Returns the last visited floor ± 0.5, depending on the previous direction.
float get_elev_floor_in_between(void);


// Sets both elevator direction and motor direction to the same direction.
void set_elev_direction(elev_motor_direction_t dir);


// Returns the elevator direction.
elev_motor_direction_t get_elev_direction(void);


// Returns the last recorded elevator direction, before the elevator stops.
elev_motor_direction_t get_elev_previous_direction(void);


// Returns true if stop button pressed.
int emergency(void);


// Stops motor and emptys current queue if stop button pressed.
void elevator_emergency_stop(void);

#endif