#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");

}

MainWindow::~MainWindow() {
    delete ui;
}




void MainWindow::on_pb_one_clicked()
{
    input_number_ = input_number_ + "1";
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}


void MainWindow::on_pb_two_clicked()
{
    input_number_ = input_number_ + "2";
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}


void MainWindow::on_pb_zero_clicked()
{
    input_number_ = input_number_ + "0";
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}


void MainWindow::on_pb_three_clicked()
{
    input_number_ = input_number_ + "3";
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}


void MainWindow::on_pb_four_clicked()
{
    input_number_ = input_number_ + "4";
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}


void MainWindow::on_pb_five_clicked()
{
    input_number_ = input_number_ + "5";
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}


void MainWindow::on_pb_six_clicked()
{
    input_number_ = input_number_ + "6";
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}


void MainWindow::on_pb_seven_clicked()
{
    input_number_ = input_number_ + "7";
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}


void MainWindow::on_pb_eight_clicked()
{
    input_number_ = input_number_ + "8";
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}


void MainWindow::on_pb_nine_clicked()
{
    input_number_ = input_number_ + "9";
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}


void MainWindow::on_pb_backspace_clicked()
{
    input_number_.chop(1);
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
    if(input_number_.isEmpty() || input_number_ == "-") {
        ui->l_result->setText("0");
    }
}


void MainWindow::on_pb_point_clicked()
{
    input_number_ = input_number_ + ".";
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}



void MainWindow::on_pb_plus_minus_clicked()
{
    QString Not_a_Number = ui->l_result->text();
    if(Not_a_Number.toLower() == "nan") {
        return;
    }
    if(Not_a_Number == "0") {
        return;
    }
    if (input_number_.startsWith('-')) {
        input_number_ = input_number_.mid(1);
    } else {
        input_number_ = "-" + input_number_;
    }
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}


void MainWindow::on_pb_save_memory_clicked()
{
    memory_cell_ = active_number_;
    memory_saved_ = true;
    ui->l_memory->setText("M");
}


void MainWindow::on_pb_load_memory_clicked()
{
    if(memory_saved_) {
       QString num = QString::number(memory_cell_);
        active_number_ = memory_cell_;
        ui->l_result->setText(num);
    }
}


void MainWindow::on_pb_clear_memory_clicked()
{
    memory_cell_ = 0;
    memory_saved_ = false;
    ui->l_memory->setText("");
}


void MainWindow::on_pb_exponentiation_clicked()
{
    if (current_operation_ == Operation::NO_OPERATION) {
        active_number_ = calculator_.GetNumber();
        calculator_.Set(active_number_);
    }
    current_operation_ = Operation::POWER;
    numb = ui->l_result->text();
    ui->l_formula->setText(numb + " ^");
    ui->l_result->setText(numb);
    input_number_.clear();
}


void MainWindow::on_pb_result_clicked()
{
    if (current_operation_ == Operation::NO_OPERATION) {
        return;
    }
    double first_numb = numb.toDouble();
    calculator_.Set(first_numb); // обновление первого числа в результате калькулятора
    QString operation_symbol;
    switch (current_operation_) {
    case Operation::ADDITION: operation_symbol = "+"; break;
    case Operation::SUBTRACTION: operation_symbol = "−"; break;
    case Operation::MULTIPLICATION: operation_symbol = "×"; break;
    case Operation::DIVISION: operation_symbol = "÷"; break;
    case Operation::POWER: operation_symbol = "^"; break;
    default: break;
    }

    ui->l_formula->setText(QString::number(calculator_.GetNumber()) + " " + operation_symbol + " " + QString::number(active_number_) + " =");
    
    switch (current_operation_) {
    case Operation::ADDITION:
        calculator_.Add(active_number_);
        break;
    case Operation::SUBTRACTION:
        calculator_.Sub(active_number_);
        break;
    case Operation::MULTIPLICATION:
        calculator_.Mul(active_number_);
        break;
    case Operation::DIVISION:
        if (active_number_ == 0) {
            return;
        }
        calculator_.Div(active_number_);
        break;
    case Operation::POWER:
        calculator_.Pow(active_number_);
        break;
    default:
        break;
    }
    active_number_ = calculator_.GetNumber();
    ui->l_result->setText(QString::number(active_number_));
    input_number_.clear();
}


void MainWindow::on_pb_division_clicked()
{
    if (current_operation_ == Operation::NO_OPERATION) {
        active_number_ = calculator_.GetNumber();
        calculator_.Set(active_number_);
    }
    current_operation_ = Operation::DIVISION;
    numb = ui->l_result->text();
    ui->l_formula->setText(numb + " ÷");
    ui->l_result->setText(numb);
    input_number_.clear();
}


void MainWindow::on_pb_multiply_clicked()
{
    if (current_operation_ == Operation::NO_OPERATION) {
        active_number_ = calculator_.GetNumber();
        calculator_.Set(active_number_);
    }
    current_operation_ = Operation::MULTIPLICATION;
    numb = ui->l_result->text();
    ui->l_formula->setText(numb + " ×");
    ui->l_result->setText(numb);
    input_number_.clear();
}


void MainWindow::on_pb_minus_clicked()
{
    if (current_operation_ == Operation::NO_OPERATION) {
        active_number_ = calculator_.GetNumber();
        calculator_.Set(active_number_);
    }
    current_operation_ = Operation::SUBTRACTION;
    numb = ui->l_result->text();
    ui->l_formula->setText(numb + " -");
    ui->l_result->setText(numb);
    input_number_.clear();
}


void MainWindow::on_pb_plus_clicked()
{
    if (current_operation_ == Operation::NO_OPERATION) {
        active_number_ = calculator_.GetNumber();
        calculator_.Set(active_number_);
    }
    current_operation_ = Operation::ADDITION;
    numb = ui->l_result->text();
    ui->l_formula->setText(numb + " +");
    ui->l_result->setText(numb);
    input_number_.clear();
}


void MainWindow::on_pb_clear_clicked()
{
    ui->l_formula->setText("");
    ui->l_result->setText("0");
    input_number_.clear();
    active_number_ = 0;
}
