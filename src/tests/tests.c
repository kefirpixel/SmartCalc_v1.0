#include <check.h>

#include "../backend/calculate.h"
#include "../backend/formatting.h"

START_TEST(calculate_1) {
  char *infix = "sin(0.8)";
  char postfix[256] = {0};

  int exit_status = infix_postfix(infix, postfix);
  ck_assert_int_eq(exit_status, OK);
  ck_assert_str_eq(postfix, "0.8 C ");
  long double result;
  calculate_postfix(postfix, 0, &result);
  ck_assert_double_eq_tol(result, sin(0.8), 1e-7);
}

START_TEST(calculate_2) {
  char *infix = "sqrt(25) + 2^3";
  char postfix[256] = {0};

  int exit_status = infix_postfix(infix, postfix);
  ck_assert_str_eq(postfix, "25 H 2 3 ^ + ");
  ck_assert_int_eq(exit_status, OK);

  long double result;
  calculate_postfix(postfix, 0, &result);
  ck_assert_double_eq_tol(result, 13.0, 1e-7);
}

START_TEST(calculate_3) {
  char *infix = "2 * (sin(0.8) + cos(1.5)) / tan(2.0)";
  char postfix[256] = {0};

  int exit_status = infix_postfix(infix, postfix);
  ck_assert_str_eq(postfix, "2 0.8 C 1.5 B + * 2.0 D / ");
  ck_assert_int_eq(exit_status, OK);

  long double result;
  calculate_postfix(postfix, 0, &result);
  ck_assert_double_eq_tol(result, 2 * (sin(0.8) + cos(1.5)) / tan(2.0), 1e-7);
}

START_TEST(calculate_4) {
  char *infix = "sqrt(-5)";
  char postfix[256] = {0};

  int exit_status = infix_postfix(infix, postfix);
  ck_assert_str_eq(postfix, "5 ~ H ");
  ck_assert_int_eq(exit_status, OK);

  long double result;
  exit_status = calculate_postfix(postfix, 0, &result);
  ck_assert_int_eq(exit_status, 3);
  ck_assert_double_eq_tol(result, 0, 1e-7);
}

START_TEST(calculate_5) {
  char *infix = "124*sqrt(-14)-247+2";
  char postfix[256] = {0};

  int exit_status = infix_postfix(infix, postfix);
  ck_assert_str_eq(postfix, "124 14 ~ H * 247 - 2 + ");
  ck_assert_int_eq(exit_status, 0);

  long double result;
  exit_status = calculate_postfix(postfix, 0, &result);
  ck_assert_int_eq(exit_status, 3);
}

START_TEST(calculate_6) {
  char *infix = "(3)6+(5+2)";
  char postfix[256] = {0};
  int exit_status = infix_postfix(infix, postfix);
  ck_assert_str_eq(postfix, "3 6 5 2 + + ");
  ck_assert_int_eq(exit_status, 0);

  long double result;
  exit_status = calculate_postfix(postfix, 0, &result);
  ck_assert_int_eq(exit_status, 3);
}

START_TEST(calculate_7) {
  char *infix = "125*(atan(12)-(-1524-1225)-236)";
  char postfix[256] = {0};
  int exit_status = infix_postfix(infix, postfix);
  ck_assert_str_eq(postfix, "125 12 G 1524 ~ 1225 - - 236 - * ");
  ck_assert_int_eq(exit_status, 0);

  long double result;
  exit_status = calculate_postfix(postfix, 0, &result);
  ck_assert_int_eq(exit_status, 0);
  ck_assert_double_eq_tol(result, 125 * (atan(12) - (-1524 - 1225) - 236),
                          1e-7);
}

START_TEST(calculate_8) {
  char *infix = "-2^2^2-(-";
  char postfix[256] = {0};
  ck_assert_int_eq(infix_postfix(infix, postfix), 2);
  ck_assert_str_eq(postfix, "");
}

START_TEST(calculate_9) {
  char *infix = "cos(tang(atan(125))*12678";
  char postfix[256] = {0};
  ck_assert_int_eq(infix_postfix(infix, postfix), 2);
  ck_assert_str_eq(postfix, "");
}

START_TEST(calculate_10) {
  char *infix = "asin(1)*ln(5)+log(25)*x-acos(0.45)";
  char postfix[256] = {0};
  int exit_status = infix_postfix(infix, postfix);
  ck_assert_str_eq(postfix, "1 F 5 I * 25 J x * + 0.45 E - ");
  ck_assert_int_eq(exit_status, OK);
  long double result;
  calculate_postfix(postfix, 5, &result);
  ck_assert_double_eq_tol(result, asin(1) * log(5) + log10(25) * 5 - acos(0.45),
                          1e-7);
}

/*calculate_credit*/
START_TEST(calc_credit_1) {
  double monthpyments = calc_month_payments_ann(100000, 12, 15);
  ck_assert_double_eq_tol(9025.83, monthpyments, 0.01);
  double totalpay = calc_total_payment(monthpyments, 12);
  ck_assert_double_eq_tol(108309.97, totalpay, 0.1);
  double overpayment = calc_over_payment(totalpay, 100000);
  ck_assert_double_eq_tol(8309.97, overpayment, 0.01);
}

START_TEST(calc_credit_2) {
  double first_pay = 0, last_pay = 0, total_pay_dif = 0;
  calc_month_payments_diff(184521, 45, 12, &first_pay, &last_pay,
                           &total_pay_dif);
  ck_assert_double_eq_tol(5945.68, first_pay, 0.01);
  ck_assert_double_eq_tol(4141.47, last_pay, 0.1);
  ck_assert_double_eq_tol(226960.83, total_pay_dif, 0.01);
  double overpayment = calc_over_payment(total_pay_dif, 184521);
  ck_assert_double_eq_tol(42439.83, overpayment, 0.01);
}

START_TEST(calc_credit_3) {
  double first_pay = 0, last_pay = 0, total_pay_dif = 0;
  calc_month_payments_diff(1085242, 120, 15, &first_pay, &last_pay,
                           &total_pay_dif);
  ck_assert_double_eq_tol(22609.21, first_pay, 0.01);
  ck_assert_double_eq_tol(9156.73, last_pay, 0.1);
  ck_assert_double_eq_tol(1905956.26, total_pay_dif, 0.01);
  double overpayment = calc_over_payment(total_pay_dif, 1085242);
  ck_assert_double_eq_tol(820714.26, overpayment, 0.01);
}

START_TEST(calc_deposit_1) {
  double totalearn = calc_total(125896, 120, 15, 12, true, 1258, 0);
  double totaltax = calc_tax_amount(totalearn, 35);
  double deposit =
      calc_total_deposit(totalearn, 125896, totaltax, 120, 1258, 0);
  ck_assert_double_eq_tol(581112.90, totalearn, 0.01);
  ck_assert_double_eq_tol(203389.51, totaltax, 0.01);
  ck_assert_double_eq_tol(654579.38, deposit, 0.01);
}

START_TEST(calc_deposit_2) {
  double totalearn = calc_total(45827, 11, 1.5, 1, false, 15288, 15);
  double totaltax = calc_tax_amount(totalearn, 38);
  double deposit =
      calc_total_deposit(totalearn, 45827, totaltax, 11, 15288, 15);
  ck_assert_double_eq_tol(1680.14, totalearn, 0.01);
  ck_assert_double_eq_tol(638.45, totaltax, 0.01);
  ck_assert_double_eq_tol(214871.69, deposit, 0.01);
}

START_TEST(calc_deposit_3) {
  double totalearn = calc_total(4582, 11, 1.5, 1, true, 15288, 15);
  double totaltax = calc_tax_amount(totalearn, 38);
  double deposit = calc_total_deposit(totalearn, 4582, totaltax, 11, 15288, 15);
  ck_assert_double_eq_tol(1117.36, totalearn, 0.01);
  ck_assert_double_eq_tol(424.60, totaltax, 0.01);
  ck_assert_double_eq_tol(173277.77, deposit, 0.01);
}

Suite *smart_calc(void) {
  Suite *s = suite_create("SmartCalcV1.0");
  TCase *calc = tcase_create("smart_calc");
  TCase *credit = tcase_create("calc_credit");
  TCase *deposit = tcase_create("calc_deposit");

  tcase_add_test(calc, calculate_1);
  tcase_add_test(calc, calculate_2);
  tcase_add_test(calc, calculate_3);
  tcase_add_test(calc, calculate_4);
  tcase_add_test(calc, calculate_5);
  tcase_add_test(calc, calculate_6);
  tcase_add_test(calc, calculate_7);
  tcase_add_test(calc, calculate_8);
  tcase_add_test(calc, calculate_9);
  tcase_add_test(calc, calculate_10);

  tcase_add_test(credit, calc_credit_1);
  tcase_add_test(credit, calc_credit_2);
  tcase_add_test(credit, calc_credit_3);

  tcase_add_test(deposit, calc_deposit_1);
  tcase_add_test(deposit, calc_deposit_2);
  tcase_add_test(deposit, calc_deposit_3);

  suite_add_tcase(s, calc);
  suite_add_tcase(s, credit);
  suite_add_tcase(s, deposit);

  return s;
}

int main(void) {
  int count_failed;
  Suite *s = smart_calc();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (count_failed == 0) ? 0 : 1;
}
