#include <math.h>
#include <stdio.h>

#include "calculate.h"

double calc_total(double deposit, int period, double int_rate, int frq_pay,
                  bool capitalization, double replenishments,
                  double withdraws) {
  double interest = int_rate * 0.01, amount_buff = deposit, total_earn = 0;
  if (period >= frq_pay) {
    for (int m = 1; m <= period; m++) {
      double buff_of_earn = 0;
      if (frq_pay == 1) {
        buff_of_earn = amount_buff * interest / 12;
      } else if (frq_pay == 12 && m % 12 == 0) {
        buff_of_earn = amount_buff * interest;
      }
      if (m < period) amount_buff = amount_buff + replenishments - withdraws;
      if (capitalization) amount_buff += buff_of_earn;
      total_earn += buff_of_earn;
    }
  }
  return total_earn;
}

double calc_tax_amount(double total_amount, double tax_rate) {
  return total_amount * tax_rate * 0.01;
}

double calc_total_deposit(double total_amount, double deposit,
                          double tax_amount, int period, double replenishments,
                          double withdraws) {
  return deposit + total_amount - tax_amount +
         ((replenishments - withdraws) * period);
}