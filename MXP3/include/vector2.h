#ifndef VECTOR2_H
#define VECTOR2_H

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>

class __declspec(dllexport) Vector2 {

public:
	double x;
	double y;

	Vector2();

	Vector2(double x_, double y_);

	virtual ~Vector2();

	Vector2 operator+(const Vector2 &oth);

	void operator+=(const Vector2 &oth);

	Vector2 operator-(const Vector2 &oth);

	void operator-=(const Vector2 &oth);

	Vector2 operator*(const Vector2 &oth);
	Vector2 operator*(const float &oth);
	Vector2 operator*=(const float &oth);
	Vector2 operator*(const double &oth);

	bool operator==(const Vector2 &oth);
	bool operator!=(const Vector2 &oth);

	void operator*=(const Vector2 &oth);

	Vector2 operator/(const Vector2 &oth);

	void operator/=(const Vector2 &oth);

	void operator/=(const float & oth);

	void operator/(const float & oth);

	Vector2 operator-(const float & oth);
	Vector2 operator+(const float & oth);

	void normalize();

	int mag();

	float angleRelTo(Vector2 pos);


private:

};

#endif // !VECTOR2_H
