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
    bool valid_position;
    elev_motor_direction_t dir;
    bool safety;
    //Queue queue_m;  
} Elevator;

// Elevator functions
int start(void);
void set_elev_floor();
int get_elev_floor();
void set_elev_direction(elev_motor_direction_t dir);
void elevator_rest();
void station_stop(elev_motor_direction_t direction, int start_time);
elev_motor_direction_t get_elev_direction();
struct Elevator* getElevator();
void floor_light_set();

void emergency_stop();

void continue_driving();

int timer_3_seconds(int start_time);

#endif