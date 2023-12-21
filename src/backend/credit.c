#include <math.h>
#include <stdio.h>

#include "calculate.h"

double calc_month_payments_ann(double summ, int period, double percente) {
  double month_percente = (percente * 0.01) / 12;
  double month_pay = summ *
                     (month_percente * (pow(1 + month_percente, period))) /
                     (pow(1 + month_percente, period) - 1);
  return month_pay;
}

double calc_total_payment(double month_pay, int term_month) {
  return month_pay * term_month;
}

double calc_over_payment(double total_payment, double summ) {
  return total_payment - summ;
}

void calc_month_payments_diff(double summ, int period, double percente,
                              double* first_pay, double* last_pay,
                              double* total_pay_dif) {
  double month_percente = (percente * 0.01) / 12;
  *first_pay = 0;
  *last_pay = 0;
  *total_pay_dif = 0;
  for (int i = 1; i <= period; i++) {
    double diff_pay =
        (summ / period) + ((summ - (i - 1) * (summ / period)) * month_percente);
    *total_pay_dif += diff_pay;
    if (i == 1)
      *first_pay = diff_pay;
    else if (i == period)
      *last_pay = diff_pay;
  }
}