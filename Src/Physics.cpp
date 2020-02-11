#include "Physics.h"

Vector2D Physics::rotate(const Vector2D& rotatingPoint, const Vector2D& point, double degrees)
{
	Vector2D v(rotatingPoint.x, rotatingPoint.y);

	float c = cos(degrees * M_PI / 180);
	float s = sin(degrees * M_PI / 180);

	v.Subtract(point);

	float newx = c * v.x - s * v.y;
	float newy = s * v.x + c * v.y;

	newx += point.x;
	newy += point.y;

	return Vector2D(newx, newy);


}