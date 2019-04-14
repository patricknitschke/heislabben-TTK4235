#ifndef LIGHTS_H
#define LIGHTS_H
#include "elevator.h"
#include "queue.h"

// Updates the floor lamp to the current floor.
void floor_light_set(void);


// Turn a button lamp on or off.
void set_lamp(elev_button_type_t button, int floor, int value);


// Turn off order lights at a floor.
void shut_lights_at_floor(int floor);


// Turn off all lights in case of emergency.
void shut_all_lights(void);


// Turns on or off the stop button lamp .
void set_stoplight(int value);


#endif