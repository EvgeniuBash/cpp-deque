#pragma once

#include "calculator.h"
#include "enums.h"

#include <QMainWindow>


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
   explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void SetInputText(const std::string& text);
    void SetErrorText(const std::string& text);
    void SetFormulaText(const std::string& text);
    void SetMemText(const std::string& text);
    void SetExtraKey(const std::optional<std::string>& key);
    void SetDigitKeyCallback(std::function<void(int key)> cb) {
       digit_cb_ = cb;
    }
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb) {
        operation_cb_ = cb;
    }
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb) {
        control_cb_ = cb;
    }
    void SetControllerCallback(std::function<void(ControllerType controller)> cb) {
        controller_cb_ = cb;
    }

private slots:

private:
    void setupDigitButtons();
    void setupOperationButtons();
    void setupControlButtons();
    void on_controllerChanged(int index);

    Ui::MainWindow *ui;
    std::function<void(int key)> digit_cb_;
    std::function<void(Operation key)> operation_cb_;
    std::function<void(ControlKey key)> control_cb_;
    std::function<void(ControllerType controller)>  controller_cb_;
};