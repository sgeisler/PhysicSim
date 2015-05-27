#include <iostream>
#include <stdio.h>
#include <cmath>

#include "Vector.h"
#include "Tensor.h"
#include "Logger.h"
//#include "Integration.h"
#include "Integration2.h"

using namespace phs;

#define PI 3.14159265358979323846


double testIntegrand(double);
Vector testIntegrand(Vector);
Vector accl(Vector);


void vectorTest()
{
	Vector a,b,c;

	a=Vector(0,8,15);
	b=Vector(13,3,7);
	
	std::cout << a.debug("  a: ") << std::endl;
	std::cout << a.getInverted().debug(" -a: ") << std::endl;
	std::cout << b.debug("  b: ") << std::endl;
	std::cout << b.getNormalized().debug("e_b: ") << std::endl;
	std::cout << c.debug("  c: ") << std::endl;
	std::cout << (a+b).debug("a+b: ") << std::endl;
	std::cout << (a-b).debug("a-b: ") << std::endl;
	std::cout << (a*b) << std::endl;
	std::cout << (a.cross(b)).debug("axb: ") << std::endl;
	std::cout << a.absSqr() << std::endl;
	std::cout << a.abs() << std::endl;
	std::cout << a.getParallelComponent(b).debug("") << std::endl;
	std::cout << a.getPerpendicularComponent(b).debug("") << std::endl;
	
	a=Vector(4,0,4);
	b=Vector(0,0,3);

	std::cout << b.debug("b: ") <<std::endl;
	std::cout << "Rotiere a um b (n-mal um 360grad/n)" << std::endl;
	double n = 6.0;
	Tensor t = b.getRotationMatrix(2*PI/n);
	std::cout << t.debug("Rotation Matrix around b") << std::endl;
	for(int c=0; c<n; c++)
	{
		std::cout << a.debug("") << "   abs:" << a.abs() << std::endl;
		a.rotate(b, 2*PI/n);
	}
	std::cout << a.debug("") << "   abs:" << a.abs() << std::endl;

	t = Tensor(1,2,3,4,5,6,7,8,9);
	std::cout << t.debug("T") << std::endl;
	t.transpose();
	std::cout << t.debug("T") << std::endl;
	t.invert();
	std::cout << t.debug("T") << std::endl;
	std::cout << t.getTransposition().getInversion().debug("T") << std::endl;
	t *= 5;
	std::cout << t.debug("T*5") << std::endl; 

}

void integrationTest()
{
	double a=0, b=2000;
	//Vector a, b;
	//a = Vector(0,0,0);
	//b = Vector(4,0,0);

	for(int c=1; c<=100; c++)
	{
		std::cout << c << std::endl;
		std::cout << "Euler Forward:" << std::endl;
		std::cout << integrate_eulerForward(testIntegrand, a, b, 1*c) << std::endl;
		//std::cout << integrate_eulerForward(testIntegrand, a, b, 1*c).debug("") << std::endl;
		std::cout << "Euler Backward:" << std::endl;
		std::cout << integrate_eulerBackward(testIntegrand, a, b, 1*c) << std::endl;
		//std::cout << integrate_eulerBackward(testIntegrand, a, b, 1*c).debug("") << std::endl;
		std::cout << "Euler Triangles:" << std::endl;
		std::cout << integrate_eulerTriangles(testIntegrand, a, b, 1*c) << std::endl;
		//std::cout << integrate_eulerTriangles(testIntegrand, a, b, 1*c).debug("") << std::endl;
		
		std::cout << '\n';
	}
}

void integration2Test()
{
	Vector s;
	Vector v;
	unsigned int delta_t = 20;

	for(unsigned int bp=1000; bp<=1000; bp++)
	{
		s = Vector(16,0,0);
		v = Vector(0,0,0);
		std::cout << bp << std::endl;
		for(unsigned int n=0; n<delta_t; n++)
		{
			phs::integrate_euler(&s, &v, accl, 1.0, bp);
			std::cout << s.debug("s:") << std::endl;
			std::cout << v.debug("   v:") << std::endl;
		}
	}
}

double testIntegrand(double x)
{
	return exp(-0.5*(x*x))/std::sqrt(2*PI);
}

Vector testIntegrand(Vector x)
{
	return Vector(0,0,x.absSqr());
}

Vector accl(Vector s)
{
	return s.getNormalized()*((-1.0)/(s*s));
}

int main()
{
    std::cout << "Hello, World!" << std::endl;

	//vectorTest();
	//integrationTest();
	integration2Test();

	std::cout << std::endl << "Press any key to quit." << std::endl;
    getchar();
    return 0;
}
