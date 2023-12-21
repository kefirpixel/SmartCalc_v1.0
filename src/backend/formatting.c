#include "formatting.h"

int is_digit(char c) { return ((c >= '0' && c <= '9') || c == 'x'); }

int is_operator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ||
          c == '%' || c == '~');
}

int is_function(char *op) {
  long double result = 0;
  if (!memcmp(op, "cos", 3))
    result = COS;
  else if (!memcmp(op, "sin", 3))
    result = SIN;
  else if (!memcmp(op, "acos", 4))
    result = ACOS;
  else if (!memcmp(op, "asin", 4))
    result = ASIN;
  else if (!memcmp(op, "atan", 4))
    result = ATAN;
  else if (!memcmp(op, "tan", 3))
    result = TAN;
  else if (!memcmp(op, "sqrt", 4))
    result = SQRT;
  else if (!memcmp(op, "ln", 2))
    result = LN;
  else if (!memcmp(op, "log", 3))
    result = LOG;
  return result;
}

int get_priority(char op) {
  int result = 0;
  if (op == '+' || op == '-') result = 0;
  if (op == '*' || op == '/') result = 1;
  if (op == '%' || op == COS || op == SIN || op == TAN || op == ACOS ||
      op == ASIN || op == ATAN || op == SQRT || op == LN || op == LOG)
    result = 2;
  if (op == '^') result = 3;
  if (op == '(' || op == ')') result = -1;
  return result;
}

void digits_to_postfix(char **infix, int *j, char *postfix) {
  while (is_digit((char)**infix) || **infix == '.' || **infix == ',' ||
         **infix == 'x') {
    postfix[*j] = **infix;
    (*j)++;
    (*infix)++;
  }
  postfix[*j] = ' ';
  (*j)++;
  (*infix)--;
}

void bracket_to_postfix(char **infix, Stack *operators) {
  push(operators, '(');
  (*infix)++;
  if (**infix == '-')
    push(operators, '~');
  else
    (*infix)--;
}

void operator_to_postfix(char **infix, int *j, Stack *operators,
                         char *postfix) {
  while (operators->top != NULL &&
         (get_priority(peek(operators)) >= get_priority(**infix))) {
    postfix[*j] = pop(operators);
    (*j)++;
    postfix[*j] = ' ';
    (*j)++;
  }
  push(operators, **infix);
}

void pow_to_postfix(char **infix, int *j, Stack *operators, char *postfix) {
  while (operators->top != NULL &&
         (get_priority(peek(operators)) > get_priority(**infix))) {
    postfix[*j] = pop(operators);
    (*j)++;
    postfix[*j] = ' ';
    (*j)++;
  }
  push(operators, **infix);
}

void function_to_postfix(char **infix, int *j, Stack *operators,
                         char *postfix) {
  while (operators->top != NULL &&
         get_priority(peek(operators)) >= get_priority(is_function(*infix))) {
    postfix[*j] = pop(operators);
    postfix[*j] = ' ';
  }
  push(operators, is_function(*infix));
}

int closed_paranthesis_postfix(int *j, Stack *operators, char *postfix) {
  int exit = 0;
  while (operators->top != NULL && peek(operators) != '(') {
    postfix[*j] = pop(operators);
    (*j)++;
    postfix[*j] = ' ';
    (*j)++;
  }
  if (peek(operators) == '(') {
    pop(operators);
  } else
    exit = 2;
  return exit;
}

int infix_postfix(char *infix, char *postfix) {
  if (infix[0] == '\0' || infix[0] == '\n') return 2;
  int j = 0, exit = 0;
  Stack *operators = (Stack *)malloc(sizeof(Stack));
  operators->top = NULL;
  if (infix[0] == '-') {
    push(operators, '~');
    ++infix;
  }
  for (; *infix != '\0' && exit == 0; ++infix) {
    if (*infix == ' ') {
      continue;
    } else if (isdigit(*infix) || *infix == 'x') {
      digits_to_postfix(&infix, &j, postfix);
    } else if (*infix == '(') {
      bracket_to_postfix(&infix, operators);
    } else if (*infix == '^') {
      pow_to_postfix(&infix, &j, operators, postfix);
    } else if (is_operator(*infix)) {
      operator_to_postfix(&infix, &j, operators, postfix);
    } else if (is_function(infix) != 0) {
      function_to_postfix(&infix, &j, operators, postfix);
      ++infix;
    } else if (*infix == ')') {
      exit = closed_paranthesis_postfix(&j, operators, postfix);
    }
  }
  while (operators->top != NULL) {
    if (peek(operators) == '(') exit = 2;
    postfix[j++] = pop(operators);
    postfix[j++] = ' ';
  }
  destroy(operators);
  if (exit != 0)
    postfix[0] = '\0';
  else
    postfix[j] = '\0';
  return exit;
}
