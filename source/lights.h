#ifndef LIGHTS_H
#define LIGHTS_H
#include "elevator.h"
#include "queue.h"

// Updates the floor lamp to the current floor.
void light_set_floor_indicator(void);


// Turn a button lamp on or off.
void light_set_lamp(elev_button_type_t button, int floor, int value);


// Turn off order lights at a floor.
void light_shut_at_floor(int floor);


// Turn off all lights in case of emergency.
void light_shut_all(void);


// Turns on or off the stop button lamp .
void light_set_stop_lamp(int value);


#endif