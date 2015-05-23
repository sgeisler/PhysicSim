#include "Vector.h"
#include "Tensor.h"


Vector::Vector()
{
	comp[0]=0.0;
	comp[1]=0.0;
	comp[2]=0.0;
}

Vector::Vector(const Vector& v)
{
	comp[0]=0.0;
	comp[1]=0.0;
	comp[2]=0.0;
}

Vector::Vector(double x, double y, double z)
{
	comp[0]=x;
	comp[1]=y;
	comp[2]=z;
}


Vector::~Vector()
{}

inline double Vector::absSqr()const
{
	return (comp[0]*comp[0]+comp[1]*comp[1]+comp[2]*comp[2]);
}