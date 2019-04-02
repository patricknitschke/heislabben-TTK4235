#ifndef MODULES_H
#define MODULES_H


#include <stdio.h>
#include "driver/elev.h"
#include "driver/io.h"

enum FLOOR_QUEUE { ONE_UP , TWO_DOWN, TWO_UP, THREE_DOWN, THREE_UP, FOUR_DOWN}; //for managing queue

void system_init();

void listen();

void drive();

int target_set();

void update_queue();

void stop();

void update_lights();

int hitchiker();

void order_kill();

int emergency_stop();




#endif
