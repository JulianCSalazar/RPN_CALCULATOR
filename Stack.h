/******************************************************************************
* File: Stack.h
* Author: Originally Max Dunne
* 	Recreated by Julian Salazar
* Date: 8/8/18
******************************************************************************/

#ifndef STACK_H
#define STACK_H

/******************************************************************************
* INCLUDED FILES
******************************************************************************/
#include "Arduino.h"

/******************************************************************************
* DEFINITIONS
******************************************************************************/
#define FALSE 0
#define TRUE 1

#define SUCCESS 1
#define STANDARD_ERROR 0
#define SIZE_ERROR 0

#define MAX_STACK_SIZE 20

/******************************************************************************
* STRUCTS
******************************************************************************/
struct Stack {
	int initialized;
	int currentItemIndex;
	float stackItems[MAX_STACK_SIZE];
};

/******************************************************************************
* FUNCTION PROTOTYPES
******************************************************************************/

/* Function: StackInit()
 * Parameters: Stack address
 * Returns: None
 * Description: This function will initialize a stack given a stack
 *	address. If a stack is being used and StackInit is called again it will
 *  reset the stack and return the item index back to -1.
 */
void StackInit(struct Stack *stack);

/* Function: StackPush()
 * Parameters: Stack address and value to be pushed to top of stack
 * Returns: SUCCESS or STANDARD_ERROR
 * Description: Pushes desired value to the top of the stack. Increments the
 *	stackItem index and returns whether the attempt was successful or not
 */
int StackPush(struct Stack *stack, float value);

/* Function: StackPop()
 * Parameters: Stack address and pointer to variable where we want to store the
 *	the popped value
 * Returns: SUCCESS or STANDARD_ERROR
 * Description: Pops the last value pushed on the stack into a variable
 *	provided by the caller. The function will return whether or not the pop was
 *	successful depending on if there were items in the stack to be popped or if
 *	if it was ever initialized.
 */
int StackPop(struct Stack *stack, float *value);

/* Function: StackIsEmpty()
 * Parameters: Stack address (read only)
 * Returns: SUCCESS or STANDARD_ERROR
 * Description: Checks stack's item index to see if stack is empty
 */
int StackIsEmpty(const struct Stack *stack);

/* Function: StackIsEmpty()
 * Parameters: Stack address (read only)
 * Returns: SUCCESS or STANDARD_ERROR
 * Description: Checks stack's item index to see if stack is full
 */
int StackIsFull(const struct Stack *stack);

/* Function: StackGetSize()
 * Parameters: Stack address (read only)
 * Returns: SUCCESS or STANDARD_ERROR
 * Description: Checks stack's item index to determine stack size
 */
int StackGetSize(const struct Stack *stack);

#endif