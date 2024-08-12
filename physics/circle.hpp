#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "vector.hpp"
#include "line.hpp"
#include "intersection.hpp"

class Circle {
public:
	Vec2 center;
	double radius;
	Circle(Vec2 center, double radius) : center(center), radius(radius) {}
	Circle() : center(Vec2(0, 0)), radius(0) {}

	Intersection intersects(const Line& l) const {
			Vec2 oc = center - l.start;
			Vec2 dir = l.end - l.start;
			double a = dot(dir, dir);
			double b = -2.0 * dot(dir, oc);
			double c = dot(oc, oc) - radius * radius;
			double discriminant = b * b - 4 * a * c;

			if(discriminant < 0) {
				return {};
			} else {
				double t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
				double t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);
				double t = std::min(t1, t2);
				Vec2 point = Vec2(l.start.x + t * dir.x, l.start.y + t * dir.y);
				Vec2 norm = (point - center).normalize();
				return {point, t, true, Vec2(0, 0)};
			}
		}
	}
};

#endif