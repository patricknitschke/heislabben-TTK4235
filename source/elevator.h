#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "elev.h"
#include "channels.h"
#include "io.h"
#include "queue.h"
#include <time.h>


#include <stdbool.h>


typedef struct Elevator {
    int floor;
    elev_motor_direction_t dir;
    elev_motor_direction_t dir_previous;
} Elevator;

// Elevator functions
int start(void);
int check_valid_floor(void);
void set_elev_floor();
int get_elev_floor();
float get_elev_floor_in_between();
void set_elev_direction(elev_motor_direction_t dir);
elev_motor_direction_t get_elev_direction();
elev_motor_direction_t get_elev_previous_direction();


void emergency_stop();

#endif