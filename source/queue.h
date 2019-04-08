#ifndef QUEUE_H
#define QUEUE_H

#include "elev.h"
#include "elevator.h"
#include "channels.h"

#include <stdbool.h>

enum floor_name {
	ONE_UP, TWO_DOWN, TWO_UP, THREE_DOWN, THREE_UP, FOUR_DOWN, NUM_FLOOR_NAMES
};


typedef struct Queue {
    int queue[NUM_FLOOR_NAMES];
    int last_queue_count;
} Queue;

void set_queue(int floor_order);
Queue* get_queue();
void pop_queue(int floor_order);

int listen();
void stop_n_kill_button();
void chase_target();
int find_target();
int queue_count();
void check_buttons_inside();




#endif