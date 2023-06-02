#include "vector.h"

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
    return Vector(x_coord_ + other.x_coord_, y_coord_ + other.y_coord_);
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(x_coord_ - other.x_coord_, y_coord_ - other.y_coord_);
}

Vector Vector::operator+() const {
    return *this;
}

Vector Vector::operator-() const {
    return Vector(-x_coord_, -y_coord_);
}

Vector Vector::operator/(int64_t number) const {
    if (number != 0) {
        return Vector(x_coord_ / number, y_coord_ / number);
    }
    return Vector();
}

Vector Vector::operator*(int64_t number) const {
    return Vector(x_coord_ * number, y_coord_ * number);
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

bool Vector::operator==(const geometry::Vector& other) const {
    return x_coord_ == other.x_coord_ && y_coord_ == other.y_coord_;
}

int64_t ScalarMult(const Vector& first, const Vector& second) {
    return first.x_coord_ * second.x_coord_ + first.y_coord_ * second.y_coord_;
}

int64_t VectorMult(const Vector& first, const Vector& second) {
    return first.x_coord_ * second.y_coord_ - first.y_coord_ * second.x_coord_;
}

double Length(Vector vector) {
    return sqrt(static_cast<double>(vector.x_coord_ * vector.x_coord_ + vector.y_coord_ * vector.y_coord_));
}
}  // namespace geometry
