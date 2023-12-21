#ifndef STACK_H
#define STACK_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define STACK_OVERFLOW 1
#define STACK_UNDERFLOW 2

typedef struct Stack {
  long double value;
  struct Stack *top;
} Stack;

void push(Stack *root, long double value);
long double pop(Stack *root);
long double peek(Stack *root);
void destroy(Stack *root);

#endif  // STACK_H
