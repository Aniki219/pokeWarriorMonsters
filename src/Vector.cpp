#include "_Headers/Vector.h"
#include <math.h>

//function to calculate the length of a vector
float Vector::magnitude()
{
	return (float)sqrt((x * x) + (y * y));
}

//addition of two vectors using + operator
Vector Vector::operator + (const Vector& v2) const
{
	return Vector(x + v2.x, y + v2.y);
}

//addition of two vectors using += operator
Vector& operator += (Vector& v1, const Vector& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;

	return v1;
}

//multiplication of a vector with a scalar number using * operator
Vector Vector::operator * (float scalar)
{
	return Vector(x * scalar, y * scalar);
}

//multiplication of a vector with a scalar number using *= operator
Vector& Vector::operator *= (float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

//subtraction of two vectors using - operator
Vector Vector::operator - (const Vector& v2) const
{
	return Vector(x - v2.x, y - v2.y);
}

//subtraction of two vectors using -= operator
Vector& operator -= (Vector& v1, const Vector& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;

	return v1;
}

//division of a vector by a scalar number using / operator
Vector Vector::operator / (float scalar)
{
	return Vector(x / scalar, y / scalar);
}

//division of a vector by a scalar number using /= operator
Vector& Vector::operator /= (float scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

//function to normalize a vector
void Vector::normalize()
{
	float l = magnitude();
	if (l > 0)	//we never want to attempt  to divide by 0
	{
		(*this) *= 1 / l;
	}
}