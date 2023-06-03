#include "segment.h"

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
}  // namespace geometry
