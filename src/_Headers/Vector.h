#pragma once

class Vector
{
public:
	float x;
	float y;

	Vector() {}	//default constructor
	Vector(float x, float y) : x(x), y(y) { }

	//finding the length of the vector
	float magnitude();

	//addition of two Vectors using + or +=
	Vector operator + (const Vector& v2) const;
	friend Vector& operator += (Vector& v1, const Vector& v2);

	//multiplication of a vector with a scalar number using * or *=
	Vector operator * (float scalar);
	Vector& operator *= (float scalar);

	//subtraction of two vector using - or -=
	Vector operator - (const Vector& v2) const;
	friend Vector& operator -= (Vector& v1, const Vector& v2);

	//division of a vector by a scalar number using / or /=
	Vector operator / (float scalar);
	Vector& operator /= (float scalar);

	//normalizing a vector
	void normalize();
};
