#ifndef SRC_CALCULATE_H
#define SRC_CALCULATE_H

#define EPSILON pow(10, -7)

#include "formatting.h"
#include "stack.h"

// nu tak prosto calculator
int calculate_postfix(char* postfix, long double x, long double* result);

// credit_calculate
double calc_month_payments_ann(double summ, int period, double percente);

double calc_total_payment(double month_pay, int term_month);

double calc_over_payment(double total_payment, double summ);

void calc_month_payments_diff(double summ, int period, double percente,
                              double* first_pay, double* last_pay,
                              double* total_pay_dif);

// deposit_calculate
double calc_total(double amount, int period, double int_rate, int frq_pay,
                  bool capitalization, double replenishments, double withdraws);

double calc_tax_amount(double total_amount, double tax_rate);

double calc_total_deposit(double total_amount, double amount, double tax_amount,
                          int period, double replenishments, double withdraws);

#endif  // SRC_CALCULATE_H
