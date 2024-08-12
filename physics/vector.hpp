#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cmath>
#include <iostream>

class Vec2 {
public:
	double x, y;

	Vec2() : x(0), y(0) {}
	Vec2(int x, int y) : x(x), y(y) {}

	// vector functions
	Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
	Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
	Vec2 operator*(const double& v) const { return Vec2(x * v, y * v); }
	Vec2 operator/(const double& v) const { return Vec2(x / v, y / v); }
	Vec2 operator-() const { return Vec2(-x, -y); }
	Vec2 add(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
	Vec2 sub(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
	Vec2 mul(const double& v) const { return Vec2(x * v, y * v); }
	Vec2 div(const double& v) const { return Vec2(x / v, y / v); }
	Vec2 neg() const { return Vec2(-x, -y); }
	Vec2 copy() const { return Vec2(x, y); }
	// self modifying functions
	Vec2& operator+=(const Vec2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	Vec2& operator-=(const Vec2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vec2& operator*=(const double& v) {
		x *= v;
		y *= v;
		return *this;
	}
	Vec2& operator/=(const double& v) {
		x /= v;
		y /= v;
		return *this;
	}
	Vec2& normalize() {
		double l = length();
		x /= l;
		y /= l;
		return *this;
	}

	// normals to the vector
	Vec2 rightNormal() const { return Vec2(-y, x); }
	Vec2 leftNormal() const { return Vec2(y, -x); }

	// scalar functions

	double length() const { return sqrt(x * x + y * y); }
	double length2() const { return x * x + y * y; }

	friend std::ostream& operator<<(std::ostream& os, const Vec2& v) {
		os << "[" << v.x << ", " << v.y << "]";
		return os;
	}
};
double dot(const Vec2& v1, const Vec2& v2) { return v1.x * v2.x + v1.y * v2.y; }

#endif