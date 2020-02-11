#pragma once
#include "Vector2D.h"
#include "SDL.h" //to include the math stuff, but all this aint necessary

class Physics
{
public:
	static Vector2D rotate(const Vector2D& rotatingPoint, const Vector2D& point, double degrees);
};