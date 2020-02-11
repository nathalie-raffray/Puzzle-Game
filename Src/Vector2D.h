#pragma once
#include <iostream>


class Vector2D
{
public:
	
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);

	bool isZero();

	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);
	float Dot(const Vector2D& vec);
	float Magnitude();

	void Normalize();

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2); 
	//return Vector2D& so as to support cascading functions, i.e. v1+v2+v3 will be
	//interpreted as (v1+v2)+v3
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	Vector2D& operator*(const int& i);
	Vector2D& Zero();

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};