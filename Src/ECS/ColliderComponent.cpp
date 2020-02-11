#include "ColliderComponent.h"



void ColliderComponent::rotateAroundPoint(Vector2D point, double degrees)
{
	//point.x = 104;
	//point.y = 104;
	
	/*Vector2D v(posObjectSpace.x, posObjectSpace.y);

	float c = cos(degrees * M_PI / 180);
	float s = sin(degrees * M_PI / 180);

	v.Subtract(point);

	float newx = c * v.x - s * v.y;
	float newy = s * v.x + c * v.y;

	newx += point.x;
	newy += point.y;*/

	Vector2D rPoint = Physics::rotate(posObjectSpace, point, degrees);

	collider.x = transform->position.x + rPoint.x;
	collider.y = transform->position.y + rPoint.y;

}

