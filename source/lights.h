/** @file
*@brief This file contains functions that control the lights.
*
*/

#ifndef LIGHTS_H
#define LIGHTS_H
#include "elevator.h"


/**
*@brief Updates the floor lamp to the current floor.
*
*/
void light_set_floor_indicator(void);


/**
*@brief Turn a button lamp on or off. Essentially an alias for elev_set_button_lamp().
*
*@param[in] button Button lamp type. Either BUTTON_CALL_UP, BUTTON_CALL_DOWN or BUTTON_COMMAND.
*@param[in] floor Floor in which the button is to be set.
*@param[in] value Value to set the button lamp to. Either 1 or 0.
*
*/
void light_set_lamp(elev_button_type_t button, int floor, int value);


// Turn off order lights at a floor.
void light_shut_at_floor(int floor);


// Turn off all lights in case of emergency.
void light_shut_all(void);


// Turns on or off the stop button lamp.
void light_set_stop_lamp(int value);


#endif