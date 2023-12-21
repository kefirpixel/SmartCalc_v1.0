#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_null, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_one, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_two, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_three, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_four, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_five, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_six, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_seven, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_eight, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_nine, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digit_numbers()));

  connect(ui->pushButton_percente, SIGNAL(clicked()), this,
          SLOT(ui_operations()));

  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(function()));

  connect(ui->pushButton_ostatok, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_umnozhit, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_razdelit, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_stepen, SIGNAL(clicked()), this, SLOT(operators()));

  ui->customplot->xAxis->setRange(-10, 10);
  ui->customplot->yAxis->setRange(-10, 10);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digit_numbers() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button != nullptr) {
    QString buttonText = button->text();
    QString current_text = ui->result_show->text();

    if (current_text == "0" || current_text == "Error") current_text.clear();

    if (buttonText == "x") {
      // Проверяем, что "x" еще не введено
      if (current_text.right(1) == 'x') {
        ui->result_show->setText(current_text + "*x");
      } else {
        ui->result_show->setText(current_text + buttonText);
      }

    } else if (buttonText == "0") {
      // После 0 добавляем точку, если 0 не входит в состав числа
      if (current_text.isEmpty() || current_text.endsWith('(')) {
        ui->result_show->setText(current_text + "0.");
      } else {
        ui->result_show->setText(current_text + buttonText);
      }
    } else {
      // Добавляем введенный символ
      ui->result_show->setText(current_text + buttonText);
    }
  }
}

void MainWindow::operators() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button != nullptr) {
    QString buttonText = button->text();
    QString current_text = ui->result_show->text();
    if (!current_text.isEmpty()) {
      QChar lastChar = current_text.back();
      if (buttonText == "-") {
        if (current_text.isEmpty()) {
          ui->result_show->setText("-");
        } else if ((lastChar == '0' && current_text.length() == 1) ||
                   (current_text.length() == 1 && current_text[0] == '+')) {
          ui->result_show->setText("-");
        } else if (lastChar == '*' || lastChar == '/' || lastChar == '^' ||
                   lastChar == '%') {
          ui->result_show->setText(ui->result_show->text() + "(-");
        } else if (lastChar == '+') {
          current_text.chop(1);
          current_text += '-';
          ui->result_show->setText(current_text);
        } else if (lastChar.isDigit() || lastChar == ')' || lastChar == 'x' ||
                   lastChar == '(' || lastChar == ' ' || lastChar == '.') {
          ui->result_show->setText(ui->result_show->text() + "-");
        }
      } else if (lastChar.isDigit() || lastChar == ')' || lastChar == 'x' ||
                 lastChar == '+' || lastChar == '-' || lastChar == '*' ||
                 lastChar == '/' || lastChar == '%' || lastChar == '^') {
        if (buttonText == "mod")
          ui->result_show->setText(current_text + "%");
        else
          ui->result_show->setText(current_text + buttonText);
      }
    }
  }
}

void MainWindow::function() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button != nullptr) {
    QString buttonText = button->text();
    QString current_text = ui->result_show->text();
    if (current_text.isEmpty() || current_text == "0" ||
        current_text == "Error") {
      ui->result_show->setText(buttonText + "(");
    } else {
      ui->result_show->setText(current_text + buttonText + "(");
    }
  }
}

int MainWindow::findLastNumberStart(const QString &text) {
  int len = text.length();
  int lastNumberStart = -1;
  for (int i = len - 1; i >= 0; i--) {
    QChar ch = text[i];
    if (ch.isDigit() || ch == '.' || (ch == '-' && !text[i - 1].isDigit())) {
      lastNumberStart = i;
    } else {
      break;
    }
  }
  return lastNumberStart;
}

void MainWindow::ui_operations() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  QString current_text = ui->result_show->text();

  if (button != nullptr) {
    if (button == ui->pushButton_percente) {
      int lastNumberStart = findLastNumberStart(current_text);
      if (lastNumberStart >= 0) {
        QString lastNumber = current_text.mid(lastNumberStart);
        double lastNumberValue = lastNumber.toDouble() * 0.01;
        current_text = current_text.left(lastNumberStart) +
                       QString::number(lastNumberValue, 'g', 15);
        ui->result_show->setText(current_text);
      }
    }
  }
}

void MainWindow::on_pushButton_point_clicked() {
  QString current_text = ui->result_show->text();
  int len = current_text.length();
  if (len == 0 || is_operator(current_text[len - 1].toLatin1()) ||
      current_text.back() == '(') {
    ui->result_show->setText(current_text + "0.");
  } else {
    int lastNumberStart = findLastNumberStart(current_text);
    if (lastNumberStart >= 0) {
      QString lastNumber = current_text.mid(lastNumberStart);
      if (!lastNumber.contains('.')) {
        ui->result_show->setText(current_text + ".");
      }
    }
  }
}

void MainWindow::on_pushButton_clear_clicked() {
  QString current_text = ui->result_show->text();

  if (!current_text.isEmpty()) {
    current_text.chop(1);
    while (!current_text.isEmpty() && current_text.back().toLatin1() >= 97 &&
           current_text.back().toLatin1() <= 122)
      current_text.chop(1);
    ui->result_show->setText(current_text);
  } else {
    ui->result_show->clear();
  }
}

void MainWindow::on_pushButton_eight_openskobka_clicked() {
  QString current_text = ui->result_show->text();
  if (current_text.isEmpty() || current_text.endsWith('0') ||
      current_text.endsWith('+') || current_text.endsWith('-') ||
      current_text.endsWith('*') || current_text.endsWith('/') ||
      current_text.endsWith('^')) {
    if (current_text.endsWith('0') && current_text.length() == 1)
      current_text.chop(1);

    ui->result_show->setText(current_text + '(');
  } else if (!(current_text.endsWith('('))) {
    ui->result_show->setText(current_text + "*(");
  }
}

void MainWindow::on_pushButton_nine_closedskobka_clicked() {
  QString current_text = ui->result_show->text();
  int openBracketsCount = current_text.count('(');
  int closeBracketsCount = current_text.count(')');

  if (openBracketsCount > closeBracketsCount && !current_text.endsWith('(')) {
    if (current_text.endsWith('0') && current_text.length() == 1)
      current_text.chop(1);
    if (current_text.back().isDigit() || current_text.back() == 'x')
      ui->result_show->setText(current_text + ')');
  }
}

void MainWindow::AddCloseBrackets() {
  QString currentText = ui->result_show->text();
  int countOpenBracket = currentText.count('('),
      countClosedBracket = currentText.count(')');
  while (!currentText.endsWith('(') && countClosedBracket < countOpenBracket) {
    currentText += ')';
    countClosedBracket++;
  }
  ui->result_show->setText(currentText);
}

void MainWindow::on_pushButton_result_clicked() {
  AddCloseBrackets();
  QByteArray infixBytes = ui->result_show->text().toUtf8();
  if (infixBytes == "Error") infixBytes = "0";
  char *infix = infixBytes.data();
  char postfix[256];

  if (infix_postfix(infix, postfix) == 0 &&
      !ui->result_show->text().isEmpty()) {
    QString xValue = ui->xEdit->toPlainText();
    bool xOk;
    double x = xValue.toDouble(&xOk);
    int countX = ui->result_show->text().count('x');

    if ((countX == 0 && !xOk) || (countX > 0 && xOk)) {
      long double resulte;
      if (calculate_postfix(postfix, x, &resulte) == 0) {
        QString stringValue = QString::number(resulte, 'f', 7);
        ui->result_show->setText(stringValue);
      } else {
        ui->result_show->setText("Error");
      }
    } else {
      ui->result_show->setText("Error");
    }
  } else {
    ui->result_show->setText("Error");
  }
}

void MainWindow::on_pushButton_eight_openskobka_2_clicked() {
  ui->result_show->setText("");
}

void MainWindow::on_pushButton_clicked() {  //кнопка для графика
  AddCloseBrackets();
  if (!ui->result_show->text().isEmpty()) {
    long double xBegin = ui->xBegin->toPlainText().toDouble();
    long double xEnd = ui->xEnd->toPlainText().toDouble();
    long double yBegin = ui->yBegin->toPlainText().toDouble();
    long double yEnd = ui->yEnd->toPlainText().toDouble();
    QByteArray infixBytes = ui->result_show->text().toUtf8();
    char *infix = infixBytes.data();
    char postfix[256];
    if (infix_postfix(infix, postfix) == 0) {
      x.clear();
      y.clear();
      ui->customplot->clearGraphs();

      bool xOk;
      QString xValue = ui->xEdit->toPlainText();
      X = xValue.toDouble(&xOk);
      if (xOk) {
        if (calculate_postfix(postfix, X, &Y) == 0) {
          if (X >= xBegin && X <= xEnd && Y >= yBegin && Y <= yEnd) {
            for (Y = yBegin; Y <= yEnd; Y += h) {
              x.push_back(X);
              y.push_back(Y);
            }
          }
        } else {
          ui->result_show->setText("Error");
        }
      } else {
        for (X = xBegin; X <= xEnd; X += h) {
          if (calculate_postfix(postfix, X, &Y) == 0) {
            if (X >= xBegin && X <= xEnd && Y >= yBegin && Y <= yEnd) {
              x.push_back(X);
              y.push_back(Y);
            }
          } else {
            ui->result_show->setText("Error");
            break;
          }
        }
      }

    } else
      ui->result_show->setText("Error");
    if (ui->result_show->text() != "Error") {
      ui->customplot->addGraph();
      QCPGraph *graph = ui->customplot->graph(0);
      QPen pen = graph->pen();
      pen.setWidth(2);
      pen.setColor(QColor::fromRgb(71, 86, 121));
      graph->setPen(pen);
      ui->customplot->graph(0)->addData(x, y);
      ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                      QCP::iSelectPlottables);
      ui->customplot->rescaleAxes();
      ui->customplot->replot();
    }
  }
}

void MainWindow::on_calculate_credit_clicked() {
  bool summOk, periodOk, percenteOk;
  double summ = ui->summ->toPlainText().toDouble(&summOk);
  int period = ui->period_month->toPlainText().toDouble(&periodOk);
  double percente = ui->percente->toPlainText().toDouble(&percenteOk);
  if (summOk && periodOk && percenteOk && summ > 0 && period > 0 &&
      percente >= 0) {
    QString type_payment = ui->payment_type->currentText();
    if (type_payment == "дифференцированный") {
      double first_pay = 0, last_pay = 0, total_pay = 0;
      calc_month_payments_diff(summ, period, percente, &first_pay, &last_pay,
                               &total_pay);
      double over_pay = calc_over_payment(total_pay, summ);
      QString first_pay_str = QString::number(first_pay, 'f', 2);
      QString last_pay_str = QString::number(last_pay, 'f', 2);
      QString total_pay_str = QString::number(total_pay, 'f', 2);
      QString over_pay_str = QString::number(over_pay, 'f', 2);
      ui->month_pay->setText(first_pay_str + " \u20BD\n" + last_pay_str +
                             " \u20BD");
      ui->calc_over_payment->setText(over_pay_str + " \u20BD");
      ui->calc_total_payment->setText(total_pay_str + " \u20BD");
    } else if (type_payment == "аннуитетный") {
      double month_pay = calc_month_payments_ann(summ, period, percente);
      double total_pay = calc_total_payment(month_pay, period);
      double over_pay = calc_over_payment(total_pay, summ);
      QString month_pay_str = QString::number(month_pay, 'f', 2);
      QString total_pay_str = QString::number(total_pay, 'f', 2);
      QString over_pay_str = QString::number(over_pay, 'f', 2);
      ui->month_pay->setText(month_pay_str + " \u20BD");
      ui->calc_over_payment->setText(over_pay_str + " \u20BD");
      ui->calc_total_payment->setText(total_pay_str + " \u20BD");
    }
  } else {
    ui->month_pay->setText("ERROR");
    ui->calc_over_payment->setText("ERROR");
    ui->calc_total_payment->setText("ERROR");
  }
}

void MainWindow::on_calc_dep_clicked() {
  bool deopOk, intrstOk, taxOk, periodOk, replOk, withOk;
  double deposit_summ = ui->deposit->toPlainText().toDouble(&deopOk);
  int period = ui->period_dep->toPlainText().toDouble(&periodOk);
  double interest_rate = ui->interest_rate->toPlainText().toDouble(&intrstOk);
  int payout_frequency =
      ui->payout_frequency->currentText() == "раз в месяц" ? 1 : 12;
  double tax_rate = ui->tax_rate->toPlainText().toDouble(&taxOk);
  bool capitalization =
      ui->capitalization->currentText() == "да" ? true : false;
  double replenishments = ui->deposits->toPlainText().toDouble(&replOk);
  double withdrawls = ui->withdrawals->toPlainText().toDouble(&withOk);
  if (deopOk && intrstOk && taxOk && periodOk && replOk && withOk &&
      deposit_summ > 0 && period > 0 && interest_rate >= 0 && tax_rate >= 0 &&
      replenishments >= 0 && withdrawls >= 0) {
    double percente_summ =
        calc_total(deposit_summ, period, interest_rate, payout_frequency,
                   capitalization, replenishments, withdrawls);
    double tax_summ = calc_tax_amount(percente_summ, tax_rate);
    double total_summ =
        calc_total_deposit(percente_summ, deposit_summ, tax_summ, period,
                           replenishments, withdrawls);
    QString percente_summ_str = QString::number(percente_summ, 'f', 2);
    QString tax_summ_str = QString::number(tax_summ, 'f', 2);
    QString total_summ_str = QString::number(total_summ, 'f', 2);
    ui->ttax_amount->setText(tax_summ_str + " \u20BD");
    ui->accumulated_interest->setText(percente_summ_str + " \u20BD");
    ui->final_summ->setText(total_summ_str + " \u20BD");
  } else {
    ui->ttax_amount->setText("ERROR");
    ui->accumulated_interest->setText("ERROR");
    ui->final_summ->setText("ERROR");
  }
}
