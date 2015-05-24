/**
 *@author Felix
 */

namespace phs
{

	double integrate_eulerForward(double(*integrand)(double), double a, double b, unsigned int precision)
	{
		double dx = b-a;
		dx /= precision;
		double integral = 0;
		for(double x=a; x<b-(dx/2.0); x+=dx)
		{
			integral += dx*integrand(x);
		}
		return integral;
	}

	double integrate_eulerBackward(double(*integrand)(double), double a, double b, unsigned int precision)
	{
		double dx = b-a;
		dx /= precision;
		double integral = 0;
		for(double x=a+dx; x<b+(dx/2.0); x+=dx)
		{
			integral += dx*integrand(x);
		}
		return integral;
	}

	double integrate_eulerTriangles(double(*integrand)(double), double a, double b, unsigned int precision)
	{
		double dx = b-a;
		dx /= precision;
		double integral = 0;
		for(double x=a; x<b-(dx/2.0); x+=dx)
		{
			integral += dx*(integrand(x)+((integrand(x+dx)-integrand(x))/2.0));
		}
		return integral;
	}

}