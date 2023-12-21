#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

extern "C" {
#include "../../backend/calculate.h"
#include "../../backend/formatting.h"
#include "../../backend/stack.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  int findLastNumberStart(const QString &text);
  void AddCloseBrackets();
  long double xBegin, xEnd, h = 0.05, X, Y;
  long double yBegin, yEnd;
  int N;

  QVector<double> x, y;

 private slots:
  void digit_numbers();
  void ui_operations();
  void operators();
  void function();
  void on_pushButton_point_clicked();
  void on_pushButton_clear_clicked();
  void on_pushButton_eight_openskobka_clicked();
  void on_pushButton_nine_closedskobka_clicked();
  void on_pushButton_result_clicked();
  void on_pushButton_eight_openskobka_2_clicked();
  void on_pushButton_clicked();
  void on_calculate_credit_clicked();
  void on_calc_dep_clicked();
};
#endif  // MAINWINDOW_H
