#include "line.h"

#include <cmath>
#include "segment.h"

namespace geometry {
Line::Line() = default;

Line::Line(Point start, Point end) {
    start_ = start;
    end_ = end;
}

int64_t Line::GetA() const {
    return start_.GetY() - end_.GetY();
}

int64_t Line::GetB() const {
    return end_.GetX() - start_.GetX();
}

int64_t Line::GetC() const {
    return -GetA() * start_.GetX() - GetB() * start_.GetY();
}

double Line::Distance(Point point) const {
    return std::abs(static_cast<double>(GetA() * point.GetX() + GetB() * point.GetY() + GetC())) /
           sqrt(static_cast<double>(GetA() * GetA() + GetB() * GetB()));
}

Line& Line::Move(const geometry::Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool Line::ContainsPoint(const Point& point) const {
    return GetA() * point.GetX() + GetB() * point.GetY() + GetC() == 0;
}

bool Line::CrossesSegment(const Segment& segment) const {
    if (ContainsPoint(segment.GetStart()) || ContainsPoint(segment.GetEnd())) {
        return true;
    }
    return ((-GetA() * segment.GetStart().GetX() - GetC()) / GetC() < segment.GetStart().GetY() &&
            (-GetA() * segment.GetEnd().GetX() - GetC()) / GetC() > segment.GetEnd().GetY()) ||
           ((-GetA() * segment.GetStart().GetX() - GetC()) / GetC() > segment.GetStart().GetY() &&
            (-GetA() * segment.GetEnd().GetX() - GetC()) / GetC() < segment.GetEnd().GetY());
}

Line* Line::Clone() const {
    return new Line(start_, end_);
}
}  // namespace geometry
