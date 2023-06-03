#include "point.h"

#include "i_shape.h"
#include "segment.h"

namespace geometry {
Point::Point(int64_t x, int64_t y) {
    x_coord_ = x;
    y_coord_ = y;
}

int64_t Point::GetX() const {
    return x_coord_;
}

int64_t Point::GetY() const {
    return y_coord_;
}

void Point::SetX(int64_t x) {
    x_coord_ = x;
}

void Point::SetY(int64_t y) {
    y_coord_ = y;
}

Point& Point::Move(const Vector& vector) {
    x_coord_ += vector.GetX();
    y_coord_ += vector.GetY();
    return *this;
}

bool Point::ContainsPoint(const Point& point) const {
    return GetX() == point.GetX() && GetY() == point.GetY();
}

bool Point::CrossesSegment(const Segment& segment) const {
    Vector start = segment.GetStart() - *this;
    Vector end = segment.GetEnd() - *this;
    Vector segment_v = segment.GetEnd() - segment.GetStart();
    return ScalarMult(start, segment_v) >= 0 && ScalarMult(end, segment_v) <= 0 && VectorMult(start, segment_v) == 0;
}

Point* Point::Clone() const {
    return new Point(GetX(), GetY());
}

Vector Point::operator-(Point other) const {
    return Vector(GetX() - other.GetX(), GetY() - other.GetY());
}
}  // namespace geometry
