#pragma once

#include <utility>

struct Vector3
{
public:
	float X() const { return _x; }
	void X(float x) { _x = std::move(x); }
	float Y() const { return _y; }
	void Y(float y) { _y = std::move(y); }
	float Z() const { return _z; }
	void Z(float z) { _z = std::move(z); }

	Vector3(float x, float y, float z) : _x(x), _y(y), _z(z) {}

	Vector3 Vector3::operator+(Vector3& other) { return Vector3(_x + other._x, _y + other._y, _z + other._z); }
	Vector3 Vector3::operator-(Vector3& other) { return Vector3(_x - other._x, _y - other._y, _z - other._z); }

private:
	float _x;
	float _y;
	float _z;
};