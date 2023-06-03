#include "segment.h"

#include "line.h"
#include "point.h"
#include "vector.h"

namespace geometry {
Segment::Segment() = default;

Segment::Segment(Point first, Point second) {
    start_ = first;
    end_ = second;
}

Point Segment::GetStart() const {
    return start_;
}

Point Segment::GetEnd() const {
    return end_;
}

double Segment::Distance(Point point) const {
    Vector v_start = Vector(point.GetX() - GetStart().GetX(), point.GetY() - GetStart().GetY());
    Vector v_end = Vector(point.GetX() - GetEnd().GetX(), point.GetY() - GetEnd().GetY());
    Vector v_segm = Vector(GetEnd().GetX() - GetStart().GetX(), GetEnd().GetY() - GetStart().GetY());

    if ((GetStart().GetX() == point.GetX() && GetStart().GetY() == point.GetY()) ||
        (GetEnd().GetX() == point.GetX() && GetEnd().GetY() == point.GetY())) {
        return 0;
    }
    if (Degenerate()) {
        return Length(v_start);
    }
    if (static_cast<double>(ScalarMult(v_start, v_segm)) / (Length(v_start) * Length(v_segm)) <= 0) {
        return Length(v_start);
    }
    if (static_cast<double>(ScalarMult(v_end, -v_segm)) / (Length(v_end) * Length(v_segm)) <= 0) {
        return Length(v_end);
    }
    return static_cast<double>(VectorMult(-v_start, -v_end)) / Length(v_segm);
}

bool Segment::Degenerate() const {
    if (GetStart().GetX() == GetEnd().GetX() && GetStart().GetY() == GetEnd().GetY()) {
        return true;
    }
    return false;
}

Segment& Segment::Move(const Vector& vector) {
    start_.SetX(GetStart().GetX() + vector.GetX());
    start_.SetY(GetStart().GetY() + vector.GetY());
    end_.SetX(GetEnd().GetX() + vector.GetX());
    end_.SetY(GetEnd().GetY() + vector.GetY());
    return *this;
}

bool Segment::ContainsPoint(const Point& point) const {
    return Line(Point(GetStart().GetX(), GetStart().GetY()), Point(GetEnd().GetX(), GetEnd().GetY()))
               .ContainsPoint(point) &&
           ((GetStart().GetX() >= point.GetX() && GetEnd().GetX() <= point.GetX()) ||
            (GetStart().GetX() <= point.GetX() && GetEnd().GetX() >= point.GetX())) &&
           ((GetStart().GetY() >= point.GetY() && GetEnd().GetY() <= point.GetY()) ||
            (GetStart().GetY() <= point.GetY() && GetEnd().GetY() >= point.GetY()));
}

bool Segment::CrossesSegment(const Segment& segment) const {
    if (Line(Point(GetStart().GetX(), GetStart().GetY()), Point(GetEnd().GetX(), GetEnd().GetY()))
            .ContainsPoint(segment.GetStart()) &&
        Line(Point(GetStart().GetX(), GetStart().GetY()), Point(GetEnd().GetX(), GetEnd().GetY()))
            .ContainsPoint(segment.GetEnd()) &&
        !segment.ContainsPoint(GetStart()) && !segment.ContainsPoint(GetEnd()) && !ContainsPoint(segment.GetStart()) &&
        !ContainsPoint(segment.GetEnd())) {
        return false;
    }
    return (Line(Point(GetStart().GetX(), GetStart().GetY()), Point(GetEnd().GetX(), GetEnd().GetY()))
                .CrossesSegment(segment)) &&
           (Line(Point(segment.GetStart().GetX(), segment.GetStart().GetY()),
                 Point(segment.GetEnd().GetX(), segment.GetEnd().GetY()))
                .CrossesSegment(*this));
}

Segment* Segment::Clone() const {
    return new Segment(GetStart(), GetEnd());
}
}  // namespace geometry
