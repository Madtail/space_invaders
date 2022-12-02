#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	const int PLAYER_WIDTH = 32;
	const int PLAYER_HEIGHT = 32;
}

class Vector2 {
public:
	float x, y;
	Vector2();
	Vector2(float x, float y);
	void sub(Vector2 v);
	void sub(float x, float y);
	void add(Vector2 v);
	void add(float x, float y);
	void mul(float f);
	Vector2 mul_N(float f);
	void normalize();
	float length();
	double angle(Vector2 v);
	void set(float x, float y);
	void fromAngle(double angle);
	void rotate(double angle);
};

#endif // GLOBALS_H