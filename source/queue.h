#ifndef QUEUE_H
#define QUEUE_H
#include "elev.h"
#include "elevator.h"
#include "channels.h"
#include "door.h"


// Queue order tags for variables in queue array.
typedef enum order_t {
	ONE_UP, TWO_DOWN, TWO_UP, THREE_DOWN, THREE_UP, FOUR_DOWN, N_ORDER_TAGS
} floor_order_t;


// A struct that contains an array with queue orders and a target floor to chase.
typedef struct Queue {
    int queue[N_ORDER_TAGS];
    int target_floor;
} Queue;


// Initialises queue array by setting it to zero.
void init_queue(void);


// Sets a target floor in Queue module.
void set_target_floor(int target);


// Places order in queue.
void set_queue(int floor_order);


// Removes order from queue.
void pop_queue(int floor_order);


// Returns zero if queue empty, non-zero if not.
int queue_count(void);


// Returns true if there exists an order above given floor.
int check_order_above_floor(int floor);


// Returns true if there exists an order below given floor.
int check_order_below_floor(int floor);


// Clear the orders from queue and turn off the lights at a particular floor.
void clear_orders_at_floor(int floor);


// Performs a check on all command buttons inside the elevator and updates the queue.
void check_buttons_inside(void);


// Performs a check on all buttons outside the elevator and updates the queue.
void check_buttons_outside(void);


// Continuously checks for orders and updates the queue and target floor.
void listen_and_find(void);


// Finds and sets a target floor based on the current queue. Targets the floor furthest away with an order.
void find_target(void);


// Sets elevator direction according to the target floor.
void chase_target(void);


// Updates the queue and lights when the elevator reaches a floor with an order. 
int stop_n_kill_button(void);


#endif