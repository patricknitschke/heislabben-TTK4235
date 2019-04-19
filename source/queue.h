/** @file
*@brief %Queue module and its corresponding functions.
*
*This file contains the queue struct and a collection of functions used to manage a functioning
*queue system.
*/
#ifndef QUEUE_H
#define QUEUE_H
#include "elevator.h"
#include "lights.h"


/**
*@enum order_t
Queue order tags for variables in @p queue array.
*
*These tags correspond to the order buttons outside the elevator. In the case of an order from the
*inside of the elevator, the order is treated as a @p order_t in @b both directions.
*
*@var ONE_UP 
*Up order button on the first floor.
*
*@var TWO_DOWN
*Down order button on the second floor.
*
*@var TWO_UP 
*Up order button on the second floor.
*
*@var THREE_DOWN
*Down order button on the third floor.
*
*@var THREE_UP 
*Up order button on the third floor.
*
*@var FOUR_DOWN
*Down order button on the fourth floor.
*
*@var N_ORDER_TAGS 
*Number of @p order_t variables.
*
*/
typedef enum order_t {
	ONE_UP, TWO_DOWN, TWO_UP, THREE_DOWN, THREE_UP, FOUR_DOWN, N_ORDER_TAGS
} floor_order_t;


/** 
*@brief Contains an array with orders and a target floor for the elevator to chase.
*
*@param queue Array of length N_ORDER_TAGS, that keeps track of the orders.
*@param target_floor The floor that the elevator aims to reach.
*
*@sa ::queue_find_target and ::queue_stop_n_serve_order for more description on @p target_floor.@n
*For information on the @p queue array variables, see ::order_t enum.
*/
typedef struct Queue {
    int queue[N_ORDER_TAGS];
    int target_floor;
} Queue;


/** 
*@brief Initialises the variables in the queue module.
*
*The variables in @p queue are set to 0. @n
*@p target_floor is set to the elevator's current floor.
*/
void queue_init(void);


/** 
*@brief Sets a target floor in the queue module.
*
*@param[in] target A floor to set the queue's @p target_floor to.
*/
void queue_set_target_floor(int target);


/** 
*@brief Places an order in @p queue.
*
*@param[in] floor_order An index in @p queue that is to be set to 1.
*/
void queue_set(int floor_order);


/** 
*@brief Removes an order from @p queue.
*
*@param[in] floor_order An index in @p queue that is to be set to 0.
*/
void queue_pop(int floor_order);


/** 
*@brief Counts the number of orders in @p queue and returns it.
*
*@returns 0 if @p queue empty. Otherwise, the number of orders in @p queue. 
*/
int queue_count(void);

 
/** 
*@brief Checks for an order by monitoring the button signals.
*
*@param button Type of button to check. Either BUTTON_CALL_UP, BUTTON_CALL_DOWN or BUTTON_COMMAND.
*@param floor Floor of the button to check.
*
*@returns 1 if the @p button on @p floor is pressed. 0 if not.
*/
int queue_get_order(elev_button_type_t button, int floor); 


/** 
*@brief Checks if there is an order above @p floor.
*
*@returns 1 if there @p queue has an order above @p floor. 0 if not.
*/
int queue_check_order_above_floor(int floor);


/** 
*@brief Checks if there is an order below @p floor.
*
*@returns 1 if there @p queue has an order below @p floor. 0 if not.
*/
int queue_check_order_below_floor(int floor);


/** 
*@brief Clear the orders from @p queue and turn off the lights at a particular floor.
*
*@param floor Floor at which to clear orders from @p queue and turn off lights.
*/
void queue_clear_orders_at_floor(int floor);


/** 
*@brief Performs a check on all command buttons inside the elevator and updates @p queue.
*
*/
void queue_check_buttons_inside(void);


/** 
*@brief Performs a check on all buttons outside the elevator and updates @p queue.
*
*/
void queue_check_buttons_outside(void);


/** 
*@brief Performs a check for @a all buttons and updates @p queue and @p target_floor.
*
*/
void queue_listen_and_find(void);


/** 
*@brief Finds and sets @p target_floor based on @p queue. 
*
*The function targets the floor furthest away with an order in the same direction. This allows 
*::queue_stop_n_serve_order to serve customers which are on the way to its targeted floor.
*/
void queue_find_target(void);


/** 
*@brief Sets the elevator direction according to @p target_floor.
*
*If @p target_floor is greater than the elevator floor, direction is set upwards and vice versa. If the
*@p target_floor is the same as the current floor, the elevator stops.
*/
void queue_chase_target(void);


/** 
*@brief Identifies when to serve a customer and serves a customer if certain conditions are met.
*
*If any of the below conditons are satisfied, ::queue_clear_orders_at_floor is called to remove orders 
*and turn off lights at the elevator's current floor.
*
*Condtions to which a customer can be served:
*@li Direction is up and same direction order exists
*@li Direction is up and no orders above
*@li Direction is down and same direction order exists
*@li Direction is down and no orders below
*@li Last order in @p queue.
*
*
*@returns 1 if the conditions to serve a customer are met. 0 otherwise.
*@note If the elevator is not on a valid floor, the function will always return 0.
*@warning Despite its name, this function <b> does not </b> physically stop the elevator. However, 
*removing orders from @p queue can result in a stop after ::queue_chase_target is called.
*/
int queue_stop_n_serve_order(void);


#endif