#pragma once
#include <cstdint>
#include <numeric>
#include <iostream>
#include <sstream>

class Rational {
public:
    Rational() : numerator_(0), denominator_(1) {}
    Rational(int numerator) : numerator_(numerator), denominator_(1) {}
    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator) {
        Reduction();
    }


    int GetNumerator() const {
        return numerator_;
    }

    int GetDenominator() const {
        return denominator_;
    }

    Rational Inv() const {
        if (numerator_ == 0) {
            throw std::invalid_argument("");
        }
        return Rational(denominator_, numerator_);
    }

    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    friend  std::ostream& operator<<(std::ostream& os,  const Rational& r) {
        os << r.numerator_;
        if (r.denominator_ != 1) {
            os << " / " << r.denominator_ ;
        }
        return os;
    }

    friend  std::istream& operator>>(std::istream& is, Rational& rational) {
        int x, y;
        char slash;

        if (!(is >> x)) {
            is.setstate(std::ios::failbit);
            return is;
        }

        if (!(is >> slash) || slash != '/') {
            rational = Rational(x, 1);
            return is;
        }

        if (!(is >> y) || y == 0) {
            is.setstate(std::ios::failbit);
            return is;
        }

        rational = Rational(x, y);
        return is;
    }


    Rational operator+(const Rational& r) const {
        Rational other(*this);
        other += r;
        return other;
    }

    Rational operator-(const Rational& r) const {
        Rational other(*this);
        other -= r;
        return other;
    }
    Rational operator*(const Rational& r) const {
        Rational other(*this);
        other *= r;
        return other;
    }

    Rational operator/(const Rational& r) const {
        Rational other(*this);
        other /= r;
        return other;
    }

    Rational& operator+=(const Rational& r) {
        numerator_ = (numerator_ * r.denominator_) + (denominator_ * r.numerator_);
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& r) {
        numerator_ = (numerator_ * r.denominator_) - (denominator_ * r.numerator_);
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator*=(const Rational& r) {
        numerator_ *= r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& r) {
        numerator_ *= r.denominator_;
        denominator_ *= r.numerator_;
        Reduction();
        return *this;
    }



    Rational& operator=(const int value) {
        numerator_ = value;
        denominator_ = 1;
        return *this;
    }

    Rational operator+() const {
        return *this;
    }

    Rational operator-() const {
        return Rational(-numerator_, denominator_);
    }



private:
    int numerator_ = 0;
    int denominator_ = 1;
};

inline auto operator<=>(const Rational& lhs, const Rational& rhs) {
    std::int64_t c1 = static_cast<std::int64_t>(lhs.GetNumerator()) * rhs.GetDenominator();
    std::int64_t c2 = static_cast<std::int64_t>(lhs.GetDenominator()) * rhs.GetNumerator();
    return c1 <=> c2;
}

inline bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() ==
           lhs.GetDenominator() * rhs.GetNumerator();
}
