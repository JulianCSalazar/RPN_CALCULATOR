/******************************************************************************
* File: Stack.h
* Author: Julian Salazar
* Description:
******************************************************************************/
#include "Arduino.h"

#define FALSE 0
#define TRUE 1

#define SUCCESS 1
#define STANDARD_ERROR 0
#define SIZE_ERROR 0

#define MAX_STACK_SIZE 20

struct Stack {
	int initialized;
	int currentItemIndex;
	float stackItems[MAX_STACK_SIZE];
};

void StackInit(struct Stack *stack);

int StackPush(struct Stack *stack, float value);

int StackPop(struct Stack *stack, float *value);

int StackIsEmpty(const struct Stack *stack);

int StackIsFull(const struct Stack *stack);

int StackGetSize(const struct Stack *stack);