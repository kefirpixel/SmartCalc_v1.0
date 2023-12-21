#include "calculate.h"

#include <stdio.h>

int calc_operator(Stack *operands, char *postfix) {
  int exit = 0;
  double operand2 = pop(operands), operand1 = pop(operands);
  if (*postfix == '+') {
    push(operands, operand1 + operand2);
  } else if (*postfix == '-') {
    push(operands, operand1 - operand2);
  } else if (*postfix == '*') {
    push(operands, operand1 * operand2);
  } else if (*postfix == '/') {
    if (operand2 != 0)
      push(operands, operand1 / operand2);
    else
      exit = SOME_ERROR;
  } else if (*postfix == '^') {
    push(operands, pow(operand1, operand2));
  } else if (*postfix == '%') {
    push(operands, fmod(operand1, operand2));
  }
  return exit;
}

int calc_func(Stack *operands, char *postfix) {
  int exit = 0;
  double operand = pop(operands);

  if (*postfix == COS) {
    push(operands, cos(operand));
  } else if (*postfix == SIN) {
    push(operands, sin(operand));
  } else if (*postfix == TAN) {
    push(operands, tan(operand));
  } else if (*postfix == ACOS) {
    push(operands, acos(operand));
  } else if (*postfix == ASIN) {
    push(operands, asin(operand));
  } else if (*postfix == ATAN) {
    push(operands, atan(operand));
  } else if (*postfix == SQRT) {
    if (operand >= 0)
      push(operands, sqrt(operand));
    else
      exit = 3;
  } else if (*postfix == LN) {
    push(operands, log(operand));
  } else if (*postfix == LOG) {
    push(operands, log10(operand));
  } else if (*postfix == '~') {
    push(operands, -1 * operand);
  }
  return exit;
}

int calculate_postfix(char *postfix, long double x, long double *result) {
  int exit = 0;
  Stack *operands = (Stack *)malloc(sizeof(Stack));
  operands->top = NULL;
  while (*postfix != '\0' && exit == 0) {
    if (*postfix == ' ') {
      ++postfix;
      continue;
    } else if (isdigit(*postfix) || (*postfix == 'x')) {
      if (*postfix == 'x') {
        push(operands, x);
        ++postfix;
      } else
        push(operands, strtold(postfix, &postfix));
    } else if (is_operator(*postfix) && *postfix != '~') {
      if (calc_operator(operands, postfix) != 0) exit = 3;
      ++postfix;
    } else if ((*postfix >= 66 && *postfix <= 74) || *postfix == '~') {
      exit = calc_func(operands, postfix);
      ++postfix;
    } else
      exit = 3;
  }
  *result = pop(operands);
  if (operands->top != NULL || isnan(*result)) exit = 3;
  destroy(operands);
  return exit;
}
