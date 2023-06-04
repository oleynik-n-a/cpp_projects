#include "vector.h"

#include <cmath>

namespace geometry {
Vector::Vector() = default;

Vector::Vector(int64_t x, int64_t y) {
    x_coord_ = x;
    y_coord_ = y;
}

int64_t Vector::GetX() const {
    return x_coord_;
}

int64_t Vector::GetY() const {
    return y_coord_;
}

Vector Vector::operator+(const Vector& other) const {
    return Vector(GetX() + other.GetX(), GetY() + other.GetY());
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(GetX() - other.GetX(), GetY() - other.GetY());
}

Vector Vector::operator+() const {
    return *this;
}

Vector Vector::operator-() const {
    return Vector(-GetX(), -GetY());
}

Vector Vector::operator/(int64_t number) const {
    if (number != 0) {
        return Vector(GetX() / number, GetY() / number);
    }
    return Vector();
}

Vector Vector::operator*(int64_t number) const {
    return Vector(GetX() * number, GetY() * number);
}

Vector& Vector::operator+=(const Vector& other) {
    *this = *this + other;
    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    *this = *this - other;
    return *this;
}

Vector& Vector::operator*=(int64_t number) {
    *this = *this * number;
    return *this;
}

Vector& Vector::operator/=(int64_t number) {
    *this = *this / number;
    return *this;
}

bool Vector::operator==(const Vector& other) const {
    return GetX() == other.GetX() && GetY() == other.GetY();
}

int64_t ScalarMult(const Vector& first, const Vector& second) {
    return first.GetX() * second.GetX() + first.GetY() * second.GetY();
}

int64_t VectorMult(const Vector& first, const Vector& second) {
    return first.GetX() * second.GetY() - first.GetY() * second.GetX();
}

double Length(Vector vector) {
    return sqrt(static_cast<double>(vector.GetX() * vector.GetX() + vector.GetY() * vector.GetY()));
}
}  // namespace geometry
