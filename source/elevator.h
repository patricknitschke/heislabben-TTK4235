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
} Elevator;

// Elevator functions
int start(void);
void set_elev_floor();
int get_elev_floor();
void set_elev_direction(elev_motor_direction_t dir);
elev_motor_direction_t get_elev_direction();


void emergency_stop();

void station_stop(elev_motor_direction_t direction); // Stops motor, maintains direction
void continue_driving(); // Continue in same direction


#endif