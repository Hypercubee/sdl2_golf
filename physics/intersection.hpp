#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP
#include "vector.hpp"

struct Intersection{
	Vec2 point;
	double t;
	bool exists;
	Vec2 normal;
	Intersection() : point(Vec2()), t(0), exists(false), normal(Vec2()) {}
	Intersection(Vec2 point, double t, bool exists, Vec2 normal) : point(point), t(t), exists(exists), normal(normal) {}
};


#endif