#include "stack.h"

void push(Stack *root, long double value) {
  Stack *newNode = (Stack *)malloc(sizeof(Stack));
  if (newNode != NULL) {
    struct Stack *temp_top = root;
    while (temp_top->top != NULL) {
      temp_top = temp_top->top;
    }
    newNode->value = value;
    newNode->top = NULL;
    temp_top->top = newNode;
  }
}

long double pop(Stack *root) {
  long double value = 0;
  if (root->top != NULL) {
    struct Stack *temp_top = root;
    while (temp_top->top->top != NULL) {
      temp_top = temp_top->top;
    }
    struct Stack *pop_value = temp_top->top;
    temp_top->top = temp_top->top->top;
    value = pop_value->value;
    free(pop_value);
  }
  return value;
}

long double peek(Stack *root) {
  struct Stack *temp_top = root;
  while (temp_top->top != NULL) {
    temp_top = temp_top->top;
  }
  long double value = temp_top->value;
  return value;
}

void destroy(struct Stack *root) {
  if (root != NULL) {
    while (root->top != NULL) {
      struct Stack *temp_top = root->top;
      root->top = root->top->top;
      free(temp_top);
    }
  }
  free(root);
}