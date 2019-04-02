#ifndef QUEUE_H
#define QUEUE_H

#include "driver/elev.h"
#include "elevator.h"
#include "driver/channels.h"

#include <stdbool.h>

enum floor_name{ONE_UP,TWO_DOWN,TWO_UP,THREE_DOWN,THREE_UP,FOUR_DOWN};


struct Queue{
    int queue[6];
};

void set_queue(int floor_order);
struct Queue* get_queue();
void pop_queue(int floor_order);

int listen();
void stop_n_kill_button();
void set_target();
int find_target();
int queue_count();




#endif