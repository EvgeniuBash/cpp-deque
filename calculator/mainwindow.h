#pragma once

#include "calculator.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void changeOperation(Operation new_operation, const QString& new_symbol);



private slots:
    void on_pb_one_clicked();

    void on_pb_two_clicked();

    void on_pb_zero_clicked();

    void on_pb_three_clicked();

    void on_pb_four_clicked();

    void on_pb_five_clicked();

    void on_pb_six_clicked();

    void on_pb_seven_clicked();

    void on_pb_eight_clicked();

    void on_pb_nine_clicked();

    void on_pb_backspace_clicked();

    void on_pb_point_clicked();

    void on_pb_plus_minus_clicked();

    void on_pb_save_memory_clicked();

    void on_pb_load_memory_clicked();

    void on_pb_clear_memory_clicked();

    void on_pb_exponentiation_clicked();

    void on_pb_result_clicked();

    void on_pb_division_clicked();

    void on_pb_multiply_clicked();

    void on_pb_minus_clicked();

    void on_pb_plus_clicked();

    void on_pb_clear_clicked();

private:
    QString input_number_;
    Calculator calculator_;
    double active_number_;
    double memory_cell_;
    bool memory_saved_;
    Operation current_operation_ = Operation::NO_OPERATION;
    Ui::MainWindow* ui;
    QString numb;
    bool isResultDisplayed = false;
    bool isMemoryNumberDisplayed = false;
};
