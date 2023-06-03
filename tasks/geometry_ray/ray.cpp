#include "ray.h"

#include "i_shape.h"
#include "line.h"
#include "segment.h"

namespace geometry {
Ray::Ray() = default;

Ray::Ray(Point first, Point second) {
    start_ = first;
    end_ = second;
}

Ray& Ray::Move(const Vector& vector) {
    start_.SetX(GetStart().GetX() + vector.GetX());
    start_.SetY(GetStart().GetY() + vector.GetY());
    end_.SetX(GetEnd().GetX() + vector.GetX());
    end_.SetY(GetEnd().GetY() + vector.GetY());
    return *this;
}

bool Ray::ContainsPoint(const Point& point) const {
    return Line(GetStart(), GetEnd()).ContainsPoint(point) && ((GetEnd().GetX() >= GetStart().GetX() &&
           GetStart().GetX() <= point.GetX()) || (GetEnd().GetX() <= GetStart().GetX() &&
           GetStart().GetX() >= point.GetX())) && ((GetEnd().GetY() >= GetStart().GetY() &&
           GetStart().GetY() <= point.GetY()) || (GetEnd().GetY() <= GetStart().GetY() &&
           GetStart().GetY() >= point.GetY()));
}

bool Ray::CrossesSegment(const Segment& segment) const {
    if (segment.ContainsPoint(GetStart()) || ContainsPoint(segment.GetStart()) || ContainsPoint(segment.GetEnd())) {
        return true;
    }

    Vector v_start = Vector(segment.GetStart().GetX() - GetStart().GetX(),
                            segment.GetStart().GetY() - GetStart().GetY());
    Vector v_end = Vector(segment.GetEnd().GetX() - GetStart().GetX(), segment.GetEnd().GetY() - GetStart().GetY());
    Vector v_direction = Vector(GetEnd().GetX() - GetStart().GetX(), GetEnd().GetY() - GetStart().GetY());
    Line line = Line(GetStart(), GetEnd());
    int64_t point_1 = line.GetA() * segment.GetStart().GetX() + line.GetB() * segment.GetStart().GetY() + line.GetC();
    int64_t point_2 = line.GetA() * segment.GetEnd().GetX() + line.GetB() * segment.GetEnd().GetY() + line.GetC();

    return ScalarMult(v_start, v_direction) >= 0 && ScalarMult(v_end, v_direction) >= 0 && point_1 * point_2 <= 0;
}

Ray* Ray::Clone() const {
    return new Ray(GetStart(), GetEnd());
}

Point Ray::GetStart() const {
    return start_;
}

Point Ray::GetEnd() const {
    return end_;
}
}  // namespace geometry
