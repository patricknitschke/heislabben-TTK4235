#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "driver/elev.h"
#include "driver/channels.h"
#include "driver/io.h"
#include "queue.h"


#include <stdbool.h>


struct Elevator{
    int floor;
    bool valid_position;
    elev_motor_direction_t dir;
    bool safety;
    //Queue queue_m;  
};

// Elevator functions
int start(void);
void set_elevator();
void setDirection(elev_motor_direction_t dir);
void elevator_rest();
void station_stop(elev_motor_direction_t direction);
elev_motor_direction_t getDirection();
struct Elevator* getElevator();


#endif