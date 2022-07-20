#pragma once
#pragma once
#include <iostream>
#include <cmath>

template <typename T>
class Vec2
{
public:
	Vec2() { x = 0; y = 0; }
	Vec2(T x, T y)
		:
		x(x), y(y)
	{}
	~Vec2() {};
	bool operator==(const Vec2& v)
	{
		if (x == vec.x && y == vec.y)
			return true;
		else
			return false;
	}
	
	bool operator!=(const Vec2& vec)
	{
		if (x != vec.x && y != vec.y)
			return true;
		else return false;
	}
	Vec2 operator+(Vec2& vec) const
	{
		return Vec2(x + vec.x, y + vec.y);
	}
	Vec2 operator-(const Vec2& vec) const
	{
		return { x - vec.x, y - vec.y };
	}
	Vec2 operator*(T d) const
	{
		return Vec2(x * d, y * d);
	}
	Vec2 operator/(T d)
	{
		return (x / d, y / d);
	}
	T Dot(const Vec2& v1)
	{
		return (v1.x * x) + (v1.y * y);
	}
	T Cross(Vec2& v1)
	{
		return (v1.x * y) - (v1.y * x);
	}
	T GetX() const
	{
		return x;
	}
	T GetY() const
	{
		return y;
	}
	T GetLength() const
	{
		return sqrt(x * x + y * y);
	}
	Vec2 Get_Normalize(const Vec2<float>& vec)
	{
		const T length = vec.GetLength();
		Vec2 norm;
		norm.x = vec.x / length;
		norm.y = vec.y / length;
		return norm;
	}
	Vec2& Normalize()
	{
		const T length = this->GetLength();
		x = x / length;
		y = y / length;
		return *this;
	}
	float Rotate(float radian)
	{
		x = x * cos(radian);
		y = y * sin(radian);
		return *this;
	}
public:
	T x, y;
};