#include "segment.h"

#include "point.h"

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
}  // namespace geometry
