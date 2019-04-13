#ifndef QUEUE_H
#define QUEUE_H

#include "elev.h"
#include "elevator.h"
#include "channels.h"
#include "door.h"

#include <stdbool.h>

enum floor_name {
	ONE_UP, TWO_DOWN, TWO_UP, THREE_DOWN, THREE_UP, FOUR_DOWN, N_FLOOR_NAMES
};


typedef struct Queue {
    int queue[N_FLOOR_NAMES];
} Queue;

void set_queue(int floor_order);
void pop_queue(int floor_order);

void listen();
int stop_n_kill_button();
void chase_target();
int find_target();
int queue_count();
void check_buttons_inside();
void check_butons_outside();

int check_order_above_floor(int floor);
int check_order_below_floor(int floor);


#endif