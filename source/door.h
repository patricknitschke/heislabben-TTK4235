#ifndef DOOR_H
#define DOOR_H
#include "elevator.h"
#include "time.h"


// Timer tags for variables in door_timer array.
enum timer_t {
    START_TIMER, TIMER_ENABLED, NUM_T_TAGS
};


// A struct that holds information regarding the door's state and timer.
typedef struct Door {
    int door_timer[NUM_T_TAGS];
    int door_is_open;
} Door;


// Initialises door module variables
void door_init(void);

// Sets TIMER_ENABLED to TRUE, START_TIMER to start time. 
void door_enable_timer(void);


// Sets TIMER_ENABLED to FALSE.
void door_reset_timer(void);


// Enables timer and turns on door lamp.
void door_open(void);


// Resets timer and turns off door lamp.
void door_close(void);


// Returns true if door is open.
int door_check_open(void);


// Returns true if timer completed.
int door_check_timer(void); 


// Returns check_timer() - true if timer completed.
int door_picked_up(void);

#endif