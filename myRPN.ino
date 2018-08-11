/*************************************************************************
 * File: myRPN.ino
 * Author: Julian Salazar
 * Date: 8/8/18
 * Description: This file 
 * Notes: This file and all relating files are derived from an assignment
 *  assigned by Professor Max Dunne for UCSC's CMPE013 course. The
 *  assignment is recreated to operate on an Arduino microcontroller as
 *  opposed to its original implementation on an UNO32. All content is
 *  original with the exception of function declarations in the header
 *  file specifing desired parameters and return types.
 ************************************************************************/

/*************************************************************************
 * INCLUDED HEADER FILES
 ************************************************************************/
 extern "C"{
  #include "Stack.h"
 }

/*************************************************************************
 * DEFINITIONS
 ************************************************************************/
#define BAUDRATE 9600
#define MAX_CHARS 60
#define TIMEOUT 60000 //In milliseconds

/*************************************************************************
 * FUNCTION PROTOTYPES
 ************************************************************************/
int CheckForChars(char *str);

/*************************************************************************
 * FUNCTIONS
 ************************************************************************/
/*
 * Function: setup()
 * Parameter: None
 * Returns: None
 * Description: Not much needs to be done other than establish serial
 *  communication with the Arduino terminal.
 */
void setup()
{
  Serial.begin(BAUDRATE);
  Serial.setTimeout(TIMEOUT);
}

/*
 * Function: loop()
 * Parameter: None
 * Returns: None
 * Description: This will serve as the main function of the code. It will
 *  welcome the user, prompt the user for a desired operation, and then
 *  perform the operation and give the user the result given that there
 *  are no errors
 */
void loop()
{
  struct Stack myStack;
  float frst; //Holds the top most value of the stack to be used in op
  float scnd; //Holds second from top value in stack to be used in op
  float userVal;
  float result;
  int errorPush, errorPop, errorChar; //Error Flags
  int inputLength;
  char input[MAX_CHARS]; //String used for user input.
  char *token; //String holding final user input with null terminator

  Serial.println("Welcome to Julian's RPN Calculator");

  while(1){
    
    //Intialize flags to SUCCESS. Changes to FAIL upon any error
    errorPush = SUCCESS; //Indicates error in push to stack
    errorPop = SUCCESS; //Indicates error in pop from stack
    errorChar = SUCCESS; //Indicates invalid user input
    
    StackInit(&myStack);

    //Asks for user input
    Serial.println("Please enter your operation(+, -, *, /):");

    //Receive user input, add null terminator
    inputLength = Serial.readBytesUntil(10, input, MAX_CHARS);
    input[inputLength - 1] = 0;

    //token assumes first user characters before white space
    token = strtok(input, " ");

    //Gives all available stack data. Use for debugging
    //Serial.println("Current Stack data is:");
    //Serial.println(myStack.initialized);
    //Serial.println(myStack.currentItemIndex);

    /* Loop runs while there are values and operators still left over from
     *  the user input string. In each iteration, we check for values from
     *  the user which will be pushed, and for operators which will pop
     *  values from the stack, operate on them, and then push the result back
     *  on.
     */
    while(token != NULL) {
      //Checks for addition operator
      Serial.print("Current token is:");
      Serial.println(token);
      if (strcmp(token, "+") == 0) {
        Serial.println("+ detected");
        errorPop = StackPop(&myStack, &frst);
        errorPop = StackPop(&myStack, &scnd);
        errorPush = StackPush(&myStack, (frst + scnd));
      //Checks for subtraction operator
      } else if (strcmp(token, "-") == 0) {
        Serial.println("- detected");
        errorPop = StackPop(&myStack, &frst);
        errorPop = StackPop(&myStack, &scnd);
        errorPush = StackPush(&myStack, (scnd - frst));
      //Checks for multiplication operator
      } else if (strcmp(token, "*") == 0) {
        Serial.println("* detected");
        errorPop = StackPop(&myStack, &frst);
        errorPop = StackPop(&myStack, &scnd);
        errorPush = StackPush(&myStack, (frst * scnd));
      //Checks for division operator
      } else if (strcmp(token, "/") == 0) {
        Serial.println("/ detected");
        errorPop = StackPop(&myStack, &frst);
        errorPop = StackPop(&myStack, &scnd);
        errorPush = StackPush(&myStack, (scnd / frst));
      /* Checks for numbers and other characters. If user inputs an
       *  invalid character, errorChar flag is triggered
       */
      } else {
        Serial.println("Other char detected");
        if (CheckForChars(token) == STANDARD_ERROR) {
          errorChar = STANDARD_ERROR;
        } else {
          userVal = atof(token);
          errorPush = StackPush(&myStack, userVal);
        }
      }

      //if there was an error, break out of the loop and print error message
      if (errorPop == STANDARD_ERROR) {
        break;
      } else if (errorPush == STANDARD_ERROR) {
        break;
      } else if (errorChar == STANDARD_ERROR) {
        break;
      }
      
      //Assigns next value or operator to token
      token = strtok(NULL, " ");
      
    } //End while(token != NULL)

    //print output of calculation if proper # of inputs was given.
    if (errorChar == STANDARD_ERROR) {
      Serial.println("ERROR: There was an error with an input char.\n");
      Serial.print("The most recent input operated on was: ");
      Serial.println(token);
    } else if (errorPop == STANDARD_ERROR) {
      Serial.println("ERROR: There was an error with the pop.\n");
      Serial.print("The most recent input operated on was: ");
      Serial.println(token);
    } else if (errorPush == STANDARD_ERROR) {
      Serial.println("ERROR: There was an error with the push.\n");
      Serial.print("The most recent input operated on was: ");
      Serial.println(token);
    } else if (StackGetSize(&myStack) == 1) {
      StackPop(&myStack, &result);
      Serial.println(result);
    } else {
      Serial.println("ERROR: more or less than one item in the stack\n");
      Serial.print("Current stack size is: ");
      Serial.println(StackGetSize(&myStack));
    }
    
  } //End while(1)

} //End loop()

/*
 * Function: CheckForChars()
 * Parameter: A string to parse
 * Returns: SUCCESS or FAILURE
 * Description: This function parses through strings entered by the user that
 *  are not identified as math operators. The function will return a SUCCESS
 *  upon finding that the entered string is a valid value entered from the user.
 *  The function returns FAIL under all other circumstances
 */
int CheckForChars(char *str)
{
    int len, i;
    char temp[len];
    len = strlen(str);
    
    /* The following loop will store each character in the string and identify
     *  any invalid characters. Valid characters are only '.' and numeric
     *  values
     */
    char *individualChar; //will hold a single char in a string for atof conversion
    for (i = 0; i < len; i++) {
        individualChar = &str[i];
        //goes through every char to check for invalid characters
        if ((temp[i] != '.') && (temp[i] != '0') && (atof(individualChar) == 0)) {
        //    return STANDARD_ERROR;
        }
    }
    return SUCCESS;
}

