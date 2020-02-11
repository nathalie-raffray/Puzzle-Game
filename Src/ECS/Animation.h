
struct Animation
{
	int index;
	int frames; //frames of the animation
	int speed; //delay between frames in milliseconds

	Animation() {}
	Animation(int i, int f, int s)
	{
		index = i;
		frames = f;
		speed = s;
	}
};