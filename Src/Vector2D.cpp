#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

bool Vector2D::isZero()
{
	if (this->x == 0 && this->y == 0) return true;
	return false;
}

Vector2D& Vector2D::Add(const Vector2D& vec) {
	x += vec.x;
	y += vec.y;
	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
	x *= vec.x;
	y *= vec.y;
	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec)
{
	x /= vec.x;
	y /= vec.y;
	return *this;
}

float Vector2D::Dot(const Vector2D& vec)
{
	return this->x * vec.x + this->y * vec.y;
}

float Vector2D::Magnitude()
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

void Vector2D::Normalize()
{
	float m = this->Magnitude();
	this->x /= m;
	this->y /= m;

}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.Subtract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.Divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->Subtract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->Divide(vec);
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.x << ", " << vec.y << ")";
	return stream;
}

Vector2D& Vector2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;
	return *this;
}

Vector2D& Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;
	return *this;
}