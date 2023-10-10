#pragma once
#include <math.h>

class Vector2
{
public: 
	float x;
	float y;

	Vector2(float x = 0.0f, float y = 0.0f)
		:x{x}, y{y}
	{	}

	friend Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	friend Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	friend Vector2 operator*(const Vector2& a, const float& scalar)
	{
		return Vector2(a.x * scalar, a.y * scalar);
	}

	float Length() 
	{
		return sqrtf(x * x + y * y);
	}

	float SquaredLength()
	{
		return x * x + y * y;
	}

	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	static float DotProd(const Vector2& a, const Vector2& b) 
	{
		return a.x * b.x + a.y * b.y;
	}
};