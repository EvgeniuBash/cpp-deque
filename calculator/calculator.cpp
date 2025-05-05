#include "calculator.h"
#include <iostream>
#include <cassert>
#include <cmath>

void Calculator::Set(Number n) {
    result_ = n;
}

Number Calculator::GetNumber() const {
    return result_;
}

void Calculator::Add(Number n) {
    result_ += n;
}

void Calculator::Sub(Number n) {
    result_ -= n;
}

void Calculator::Div(Number n) {
    result_ /= n;
}


void Calculator::Mul(Number n) {
    result_ *= n;
}

void Calculator::Pow(Number n) {
    result_ = std::pow(result_, n);
}

void Calculator::Save() {
    save_value_ = result_;
    is_save_memory_empty_ = false;
}

void Calculator::Load() {
    if (is_save_memory_empty_) {
        std::cerr << "Error: Memory is empty" << std::endl;
    } else {
        result_ = save_value_;
    }
}

bool Calculator::HasMem() const {
    return !is_save_memory_empty_;
}

std::string Calculator::GetNumberRepr() const {
    return std::to_string(result_);
}
