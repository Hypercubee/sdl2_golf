#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "intersection.hpp"
#include "line.hpp"
#include "vector.hpp"

class Circle {
public:
	Vec2 center;
	double radius;
	Circle(Vec2 center, double radius) : center(center), radius(radius) {}
	Circle() : center(Vec2(0, 0)), radius(0) {}
};

#endif