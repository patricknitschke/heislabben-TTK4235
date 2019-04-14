#ifndef DOOR_H
#define DOOR_H

#include "elevator.h"
#include "time.h"
#include "lights.h"


// Timer tags for variables in door_timer array.
enum timer_t {
    START_TIMER, TIMER_ENABLED, NUM_T_TAGS
};


// A struct that holds information regarding the door's state and timer.
typedef struct Door {
    int door_timer[NUM_T_TAGS];
    int door_is_open;
} Door;


// Sets TIMER_ENABLED to TRUE, START_TIMER to start time. 
void enable_timer();


// Sets TIMER_ENABLED to FALSE.
void reset_timer();


// Enables timer and turns on door lamp.
void open_door();


// Resets timer and turns off door lamp.
void close_door();


// Returns true if door is open.
int check_door_open();


// Returns true if timer completed.
int check_timer(); 


// Returns check_timer() - true if timer completed.
int picked_up();

#endif