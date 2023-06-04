#include "polygon.h"

#include <cmath>

#include "line.h"
#include "point.h"
#include "segment.h"
#include "vector.h"

namespace geometry {
Polygon::Polygon() = default;

Polygon::Polygon(std::vector<Point> points) {
    points_ = points;
    num_points_ = points.size();
}

Polygon& Polygon::Move(const Vector& vector) {
    for (size_t i = 0; i < num_points_; ++i) {
        points_[i].SetX(points_[i].GetX() + vector.GetX());
        points_[i].SetY(points_[i].GetY() + vector.GetY());
    }
    return *this;
}

bool Polygon::ContainsPoint(const Point& point) const {
    for (size_t i = 0; i < num_points_; ++i) {
        if (Segment(points_[i], points_[(i + 1) % num_points_]).ContainsPoint(point)) {
            return true;
        }
    }
    double angles_sum = 0;
    const double eps = 10e-11;
    for (size_t i = 0; i < num_points_; ++i) {
        if (!Line(point, points_[i]).ContainsPoint(points_[(i + 1) % num_points_])) {
            Vector v1 = points_[i] - point;
            Vector v2 = points_[(i + 1) % num_points_] - point;
            Vector v3 = points_[i] - points_[(i + 1) % num_points_];
            angles_sum +=
                acos((pow(Length(v1), 2) + pow(Length(v2), 2) - pow(Length(v3), 2)) / (2 * Length(v1) * Length(v2)));
        }
    }
    return angles_sum >= 2 * std::numbers::pi - eps && angles_sum <= 2 * std::numbers::pi + eps;
}

bool Polygon::CrossesSegment(const Segment& segment) const {
    for (size_t i = 0; i < num_points_; ++i) {
        if (segment.CrossesSegment(Segment(points_[i], points_[(i + 1) % num_points_]))) {
            return true;
        }
    }
    return false;
}

Polygon* Polygon::Clone() const {
    return new Polygon(points_);
}
}  // namespace geometry
