/** @file
*@brief Functions used to operate the lights of the elevator.
*
*These functions are sufficient in operating the lights of the elevator. Some are wrappers for
*functions supplied by elev.h.
*/
#ifndef LIGHTS_H
#define LIGHTS_H
#include "elevator.h"


/**
*@brief Sets the elevator floor indicator to the current floor.
*/
void light_set_floor_indicator(void);


/**
*@brief Turn a button lamp on or off. Essentially an alias for ::elev_set_button_lamp.
*
*@param[in] button Button lamp type. Either BUTTON_CALL_UP, BUTTON_CALL_DOWN or BUTTON_COMMAND.
*@param[in] floor Floor in which the button is to be set.
*@param[in] value Value to set the button lamp to. Either 1 or 0, where 1 is on.
*
*/
void light_set_lamp(elev_button_type_t button, int floor, int value);


/**
*@brief Turns off all button lamps at @p floor.
*
*@param[in] floor Floor where lights are to be turned off.
*/
void light_shut_at_floor(int floor);


/**
*@brief Turns off all button lamps on the elevator.
*/
void light_shut_all(void);


/**
*@brief Turns on or off the stop button lamp.
*
*@param[in] value Value to set the stop lamp to. Either 1 or 0, where 1 is on.
*/
void light_set_stop_lamp(int value);


#endif