#ifndef DOOR_H
#define DOOR_H

#include "elevator.h"
#include "queue.h"
#include "elev.h"
#include "time.h"

enum timer_tag {
    START_TIMER, TIMER_ENABLED, NUM_T_TAGS
};

typedef struct Door {
    int door_timer[NUM_T_TAGS];
} Door;

int start_timer();
int timer_enabled();
void reset_timer();

void open_door();
void close_door();

int check_timer(); 
int picked_up(); // returns true when timer completed

void remove_target(int floor);


#endif