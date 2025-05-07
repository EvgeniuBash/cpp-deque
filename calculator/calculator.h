
#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"

using Error = std::string;

template <typename Number>
class Calculator {
public:

    void Load() {
        if (mem_) {
            result = *mem_;
        } else {
            result = Number();
        }
    }

    void Save() {
        mem_ = result;
    }

    bool GetHasMem() const {
        return mem_.has_value();
    }

    void Set(const Number& n) {
        result = n;
    }

    Number GetNumber() const {
        return result;
    }
    // Сложение
    std::optional<Error> Add(const Number& n) {
        result += n;
        return std::nullopt;
    }
    // Вычитание
    std::optional<Error> Sub(const Number& n) {
        result -= n;;
        return std::nullopt;
    }
    // Деление
    std::optional<Error> Div(const Number& n) {
        if constexpr (std::is_floating_point_v<Number>) {
            if (n == 0.0) {
                result = (result > 0) ? std::numeric_limits<Number>::infinity() : std::numeric_limits<Number>::infinity() * -1;
                return std::nullopt; 
            }
        } else {
            if (n == 0) {
                return "Division by zero"; 
            }
        }
        result /= n; 
        return std::nullopt; 
    }
    // Умножение
    std::optional<Error> Mul(const Number& n) {
        result *= n;
        return std::nullopt;
    }
    // Возведение в степень
    std::optional<Error> Pow(const Number& n) {
        if constexpr (std::is_integral_v<Number>) {
            if (result == 0 && n == 0) {
                return "Zero power to zero";
            }
            if (n < 0) {
                return "Integer negative power";
            }
            result = IntegerPow(result, n);
            return std::nullopt;
        }
        else if constexpr (std::is_same_v<Number, Rational>) {
            if (result.GetNumerator() == 0 && result.GetDenominator() == 1 && n.GetNumerator() == 0 && n.GetDenominator() == 1) {
                return "Zero power to zero";
            }
            if (n.GetDenominator() != 1) {
                return "Fractional power is not supported";
            }
            result = ::Pow(result, n);
            return std::nullopt;
        }
        else if constexpr (std::is_floating_point_v<Number>) {
            result = std::pow(result, n);
            return std::nullopt;
        }
        else {
            return "Unsupported type for power operation";
        }
    }

private:
    Number result;
    std::optional<Number> mem_ = std::nullopt;

};
