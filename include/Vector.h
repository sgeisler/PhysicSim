#pragma once
#include "Tensor.h"
#include <string>

class Vector
{
	double comp[3];
public:
	Vector();
	Vector(const Vector&);
	Vector(double x, double y, double z);

	inline double getX()const{return comp[0];}
	inline double getY()const{return comp[1];}
	inline double getZ()const{return comp[2];}

	inline void setX(double d);
	inline void setY(double d);
	inline void setZ(double d);

	inline double absSqr()const;
	inline double abs()const;

	Vector operator=(const Vector&);

	void normalize();
	void invert();
	void operator+=(const Vector&);
	void operator-=(const Vector&);
	void operator*=(const double);
	void operator*=(const Tensor&);
	
	Vector getNormalized();
	Vector getInverted();
	Vector operator+(const Vector&);
	Vector operator-(const Vector&);
	Vector operator*(const double);
	double operator*(const Vector&);
	Vector operator*(const Tensor&);
	Vector cross(const Vector&);

	Vector getParallelComponent(const Vector&);
	Vector getPerpendicularComponent(const Vector&);

	void rotate(const Vector&, double);
	void rotate(const Vector&);

	Vector getRotation(const Vector&, double);
	Vector getRotation(const Vector&);

	std::string debug(std::string);

	~Vector();
};

