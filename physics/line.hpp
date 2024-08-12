#ifndef LINE_HPP
#define LINE_HPP
#include "intersection.hpp"
#include "vector.hpp"

class Line {
public:
	Vec2 start;
	Vec2 end;
	Line() : start(Vec2()), end(Vec2()) {}
	Line(Vec2 start, Vec2 end) : start(start), end(end) {}
	Line(double x1, double y1, double x2, double y2) : start(Vec2(x1, y1)), end(Vec2(x2, y2)) {}

	Line copy() const { return Line(start, end); }
	Vec2 leftNormal() const { return Vec2(start.y - end.y, end.x - start.x).rightNormal(); }
	Vec2 rightNormal() const { return Vec2(start.y - end.y, end.x - start.x).leftNormal(); }

	Intersection intersects(const Line& l) const {
		Vec2 p1 = l.start;
		Vec2 p2 = l.end;
		Vec2 q1 = start;
		Vec2 q2 = end;
		Vec2 r = p2 - p1;
		Vec2 s = q2 - q1;
		Vec2 norm = r.rightNormal().normalize();
		if(dot(s, norm) > 0) return {};
		double rxs = r.x * s.y - r.y * s.x;
		if(rxs == 0) return {};
		double t = ((q1.x - p1.x) * s.y - (q1.y - p1.y) * s.x) / rxs;
		double u = ((q1.x - p1.x) * r.y - (q1.y - p1.y) * r.x) / rxs;
		Vec2 point = Vec2(p1.x + t * r.x, p1.y + t * r.y);
		// if (dot(point - p1, norm) > 0) return {};
		return {point, t, true, norm};
	}
};

#endif