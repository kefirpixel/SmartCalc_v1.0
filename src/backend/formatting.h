#ifndef SRC_FORMATTING_H
#define SRC_FORMATTING_H
#include <ctype.h>
#include <string.h>

#include "stack.h"

#define ERROR_LONG_EXPRESSION 1
#define MISMATCHED_PARENTHESIS 2
#define SOME_ERROR 3

enum Operator {
  COS = 66,   // B
  SIN = 67,   // C
  TAN = 68,   // D
  ACOS = 69,  // E
  ASIN = 70,  // F
  ATAN = 71,  // G
  SQRT = 72,  // H
  LN = 73,    // I
  LOG = 74,   // J
};

int string_input(char *infix);
int is_digit(char c);
long double if_function(char *op);
int get_priority(char op);
int string_parser(const char *str, Stack *stack, long double value);
int infix_postfix(char *infix, char *postfix);
int is_operator(char c);

#endif  // SRC_FORMATTING_H
