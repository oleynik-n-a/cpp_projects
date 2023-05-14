#include "rational.h"

int64_t Sgn(int64_t value) {
    return (value > 0) - (value < 0);
}

Rational::Rational() {
    numer_ = 0;
    denom_ = 1;
}

Rational::Rational(int value) {
    numer_ = value;
    denom_ = 1;
}

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    int64_t nod = std::gcd(numer, denom);
    numer_ = static_cast<int>(Sgn(denom / nod) * numer / nod);
    denom_ = static_cast<int>(std::abs(denom / nod));
}

Rational::Rational(int numer, int denom) {
    Set(numer, denom);
}

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {
    Set(value, GetDenominator());
}

void Rational::SetDenominator(int value) {
    Set(GetNumerator(), value);
}

Rational operator+(const Rational& ratio) {
    return ratio;
}

Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int64_t tmp_numer = lhs.GetNumerator() * rhs.GetDenominator() + rhs.GetNumerator() * lhs.GetDenominator();
    int64_t tmp_denom = lhs.GetDenominator() * rhs.GetDenominator();
    lhs.Set(tmp_numer, tmp_denom);
    return lhs;
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    return lhs += -rhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs.Set(lhs.GetNumerator() * rhs.GetNumerator(), lhs.GetDenominator() * rhs.GetDenominator());
    return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    return lhs *= Rational(rhs.GetDenominator(), rhs.GetNumerator());
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    return result += rhs;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    return result -= rhs;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    return result *= rhs;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    return result /= rhs;
}

Rational& operator++(Rational& ratio) {
    return ratio += Rational(1);
}

Rational operator++(Rational& ratio, int) {
    Rational result = ratio;
    ++ratio;
    return result;
}

Rational& operator--(Rational& ratio) {
    return ratio -= Rational(1);
}

Rational operator--(Rational& ratio, int) {
    Rational result = ratio;
    --ratio;
    return result;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() == rhs.GetNumerator() && lhs.GetDenominator() == rhs.GetDenominator();
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return Sgn((lhs - rhs).GetNumerator()) == -1;
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return Sgn((lhs - rhs).GetNumerator()) == 1;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return lhs > rhs || lhs == rhs;
}

std::ostream& operator<<(std::ostream& ostream, const Rational& ratio) {
    ostream << ratio.GetNumerator();
    ratio.GetDenominator() == 1 ? ostream : ostream << '/' << ratio.GetDenominator();
    return ostream;
}

std::istream& operator>>(std::istream& istream, Rational& ratio) {
    int numer = 1;
    int denom = 1;
    istream >> numer;
    if (istream.peek() == '/') {
        istream.ignore();
        istream >> denom;
    }
    ratio.Set(numer, denom);
    return istream;
}
