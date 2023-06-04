#include "circle.h"

#include <cmath>

#include "segment.h"

namespace geometry {
Circle::Circle() = default;

Circle::Circle(Point centre, int64_t radius) {
    centre_ = centre;
    radius_ = radius;
}

Circle& Circle::Move(const Vector& vector) {
    centre_.SetX(GetCenter().GetX() + vector.GetX());
    centre_.SetY(GetCenter().GetY() + vector.GetY());
    return *this;
}

bool Circle::ContainsPoint(const Point& point) const {
    return Length((point - GetCenter())) <= static_cast<double>(GetRadius());
}

bool Circle::CrossesSegment(const Segment& segment) const {
    if ((ContainsPoint(segment.GetStart()) && !ContainsPoint(segment.GetEnd())) ||
        (!ContainsPoint(segment.GetStart()) && ContainsPoint(segment.GetEnd())) ||
        Length((segment.GetStart() - GetCenter())) == static_cast<double>(GetRadius()) ||
        Length((segment.GetEnd() - GetCenter())) == static_cast<double>(GetRadius())) {
        return true;
    }
    return segment.Distance(GetCenter()) <= static_cast<double>(GetRadius()) && !ContainsPoint(segment.GetStart()) &&
           !ContainsPoint(segment.GetEnd());
}

Circle* Circle::Clone() const {
    return new Circle(GetCenter(), GetRadius());
}

int64_t Circle::GetRadius() const {
    return radius_;
}

Point Circle::GetCenter() const {
    return centre_;
}
}  // namespace geometry
