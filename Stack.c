/******************************************************************************
* File: Stack.c
* Author: Julian Salazar
* Date: 8/8/18
* Description: This file holds all stack operating functions.
******************************************************************************/

/******************************************************************************
* Libraries
******************************************************************************/
#include "Stack.h"
#include "Arduino.h"

/******************************************************************************
* Variables
******************************************************************************/
int i;

/******************************************************************************
* FUNCTIONS
******************************************************************************/
/* Function: StackInit()
 * Parameters: Stack address
 * Returns: None
 * Description: This function will initialize a stack given the stack
 *	address. If a stack is being used and StackInit is called again it will
 *  reset the stack and return the item index back to -1.
 */
void StackInit(struct Stack *stack)
{
    stack->initialized = SUCCESS;
    i = -1;
    stack->currentItemIndex = i;
}

/* Function: StackPush()
 * Parameters: Stack address and value to be pushed to top of stack
 * Returns: SUCCESS or STANDARD_ERROR
 * Description: Pushes desired value to the top of the stack. Increments the
 *	stackItem index and returns whether the attempt was successful or not
 */
int StackPush(struct Stack *stack, float value)
{
    if (StackIsFull(stack) || (stack->initialized == STANDARD_ERROR)) {
        return STANDARD_ERROR;
    } else {
        stack->stackItems[++i] = value;
        stack->currentItemIndex = i;
        return SUCCESS;
    }
}

/* Function: StackPop()
 * Parameters: Stack address and pointer to variable where we want to store the
 *	the popped value
 * Returns: SUCCESS or STANDARD_ERROR
 * Description: Pops the last value pushed on the stack into a variable
 *	provided by the caller. The function will return whether or not the pop was
 *	successful depending on if there were items in the stack to be popped or if
 *	if it was ever initialized.
 */
int StackPop(struct Stack *stack, float *value)
{
    if ((StackIsEmpty(stack)) || (stack->initialized == STANDARD_ERROR)) {
        return STANDARD_ERROR;
    } else {
        *value = stack->stackItems[i--];
        stack->currentItemIndex = i;
        return SUCCESS;
    }
}

/* Function: StackIsEmpty()
 * Parameters: Stack address (read only)
 * Returns: SUCCESS or STANDARD_ERROR
 * Description: Checks stack's item index to see if stack is empty
 */
int StackIsEmpty(const struct Stack *stack)
{
    if ((stack->currentItemIndex == -1) && (stack->initialized == SUCCESS)) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

/* Function: StackIsEmpty()
 * Parameters: Stack address (read only)
 * Returns: SUCCESS or STANDARD_ERROR
 * Description: Checks stack's item index to see if stack is full
 */
int StackIsFull(const struct Stack *stack)
{
    if ((stack->currentItemIndex == (MAX_STACK_SIZE - 1)) 
		&& (stack->initialized == SUCCESS)) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

/* Function: StackGetSize()
 * Parameters: Stack address (read only)
 * Returns: SUCCESS or STANDARD_ERROR
 * Description: Checks stack's item index to determine stack size
 */
int StackGetSize(const struct Stack *stack)
{
    if (stack->initialized == SUCCESS){
        return (1 + (stack->currentItemIndex));
    } else {
        return SIZE_ERROR;
    }
    
}