#ifndef LIGHTS_H
#define LIGHTS_H

#include "elevator.h"
#include "queue.h"
#include "elev.h"

void kill_all_lights();

void update_lights(elev_button_type_t button, int floor, int value);
void floor_light_set();
void set_stoplight(int value);

int get_order(elev_button_type_t button, int floor); // Alias for get button signal



#endif