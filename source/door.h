/** @file
*@brief Functions used to operate the doors of the elevator.
*
*These functions are sufficient in operating a door and its lights. Utilises a timer, @a clock(),
*from %time.h.
*/
#ifndef DOOR_H
#define DOOR_H
#include "elevator.h"
#include "time.h"


/**
*@enum tag_timer 
*Timer tags for variables in @p door_timer array.
*
*@var START_TIMER 
*Timestamp at which the door opens.
*
*@var TIMER_ENABLED
*1 if the timer is enabled, 0 if not.
*
*@var N_TIMER_TAGS 
*Number of variables in @p door_timer array.
*
*/
typedef enum tag_timer {
    START_TIMER, TIMER_ENABLED, N_TIMER_TAGS
} timer_t;


/**
*@brief A struct that holds information regarding the door's state and timer.
*
*@param door_timer Array of length N_TIMER_TAGS, with variables used to control the door timer. 
*@param door_is_open Keeps track of the door's state. 1 if the door is open, 0 if closed.
*@sa ::tag_timer enum for variables in @p door_timer.
*/
typedef struct Door {
    int door_timer[N_TIMER_TAGS];
    int door_is_open;
} Door;


/**
*@brief Initialises door module variables
*
*Sets @p door_timer variables to 0.@n
*Sets @p door_is_open to 0.
*/
void door_init(void);


/**
*@brief Enables the timer and registers the start time.
*
*Sets TIMER_ENABLED to 1 and START_TIMER to the current time, @a clock().
*/
void door_enable_timer(void);


/**
*@brief Disables the timer.
*
*Sets TIMER_ENABLED to 0.
*/
void door_reset_timer(void);


/**
*@brief Starts the timer and turns on door lamp.
*
*Calls upon ::door_enable_timer, sets @p door_is_open to 1 and turns on the door lamp.
*/
void door_open(void);


/**
*@brief Resets timer and turns off door lamp.
*
*Calls upon ::door_reset_timer, sets @p door_is_open to 0 and turns off the door lamp.
*/
void door_close(void);


/**
*@brief Checks if the door is open using @p door_is_open.
*
*@returns @p door_is_open variable.
*/
int door_check_open(void);


/**
*@brief Checks if the door timer of 3 seconds has completed.
*
*@returns 1 if the 3 seconds have elapsed, 0 if not.
*/
int door_check_timer(void); 


/**
*@brief Alias for ::door_check_timer.
*
*Checks if customers have entered the elevator through the timer. 
*
*@returns ::door_check_timer.
*/
int door_picked_up(void);

#endif