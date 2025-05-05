#pragma once

#include <string>
#include <cmath>
#include <limits>

enum class Operation {
    NO_OPERATION,          //операция не задана
    ADDITION,              //плюс
    SUBTRACTION,           //минус
    MULTIPLICATION,        //умножить
    DIVISION,              //поделить
    POWER                  //возведение в степень
};


using Number = double;

class Calculator {
public:

    void Set(Number n);

    Number GetNumber() const;

    void Add(Number n);

    void Sub(Number n);

    void Div(Number n);

    void Mul(Number n);

    void Pow(Number n);

    void Save();

    void Load();

    bool HasMem() const;

    std::string GetNumberRepr() const;



private:
    Number save_value_ = 0.0;
    bool is_save_memory_empty_ = true;
    Number result_ = 0.0;

};
