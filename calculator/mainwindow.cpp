#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
    setupDigitButtons();
    setupOperationButtons();
    setupControlButtons();

     connect(ui->cmb_controller, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_controllerChanged);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setStyleSheet("font-size: 16px;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setStyleSheet("color: red; font-size: 16px;");
    ui->l_result->setText(QString::fromStdString(text));
}

void  MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void  MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (key) {
        ui->tb_extra->setText(QString::fromStdString(*key));
        ui->tb_extra->show();
    } else {
        ui->tb_extra->hide();
    }
}



void MainWindow::setupDigitButtons() {
    for (int i = 0; i < 10; ++i) {
        QPushButton* button = findChild<QPushButton*>(QString("pb_%1").arg(i));
        connect(button, &QPushButton::clicked, [this, i]() {
            if (digit_cb_) {
                digit_cb_(i);
            }
        });
    }
}

void MainWindow::setupOperationButtons() {
    connect(ui->pb_plus, &QPushButton::clicked, [this]() {
        if (operation_cb_) {
            operation_cb_(Operation::ADDITION);
        }
    });
    connect(ui->pb_minus, &QPushButton::clicked, [this]() {
        if (operation_cb_) {
            operation_cb_(Operation::SUBTRACTION);
        }
    });
    connect(ui->pb_multiply, &QPushButton::clicked, [this]() {
        if (operation_cb_) {
            operation_cb_(Operation::MULTIPLICATION);
        }
    });
    connect(ui->pb_division, &QPushButton::clicked, [this]() {
        if (operation_cb_) {
            operation_cb_(Operation::DIVISION);
        }
    });
    connect(ui->pb_exponentiation, &QPushButton::clicked, [this]() {
        if (operation_cb_) {
            operation_cb_(Operation::POWER);
        }
    });
}

void MainWindow::on_controllerChanged(int index) {

    QString selectedText = ui->cmb_controller->currentText();
    ControllerType controllerType;

    if (selectedText == "double") {
        controllerType = ControllerType::DOUBLE;
    } else if (selectedText == "float") {
        controllerType = ControllerType::FLOAT;
    } else if (selectedText == "uint8_t") {
        controllerType = ControllerType::UINT8_T;
    } else if (selectedText == "int") {
        controllerType = ControllerType::INT;
    } else if (selectedText == "int64_t") {
        controllerType = ControllerType::INT64_T;
    } else if (selectedText == "size_t") {
        controllerType = ControllerType::SIZE_T;
    } else if (selectedText == "Rational") {
        controllerType = ControllerType::RATIONAL;
    }

    if (controller_cb_) {
        controller_cb_(controllerType);
    }
}

void MainWindow::setupControlButtons() {
    connect(ui->pb_result, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::EQUALS);
        }
    });
    connect(ui->pb_clear, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::CLEAR);
        }
    });
    connect(ui->pb_save_memory, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::MEM_SAVE);
        }
    });
    connect(ui->pb_load_memory, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::MEM_LOAD);
        }
    });
    connect(ui->pb_clear_memory, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::MEM_CLEAR);
        }
    });
    connect(ui->pb_plus_minus, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::PLUS_MINUS);
        }
    });
    connect(ui->pb_backspace, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::BACKSPACE);
        }
    });
    connect(ui->tb_extra, &QPushButton::clicked, [this]() {
        if (control_cb_) {
            control_cb_(ControlKey::EXTRA_KEY);
        }
    });
}
