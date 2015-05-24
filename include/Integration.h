/**
 *@author Felix
 */

namespace phs
{
	/**
	 * ints that specify integration methods
	 */
	unsigned short live_integration_method=0, cache_integration_method=0;
	unsigned const short PHS_INTEGRATION_EULER_FORWARD=0, PHS_INTEGRATION_EULER_BACKWARD=1, PHS_INTEGRATION_EULER_TRIANGLES=2; 

	/**
	 * specific integration methods
	 */
	double integrate_eulerForward(double(*integrand)(double), double a, double b, unsigned int precision)
	{
		double dx = b-a;
		dx /= precision;
		double integral = 0;
		for( double x=a; a<=x&&x<b-(dx/2.0) || a>=x&&x>b+(dx/2.0); x+=dx )
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
		for( double x=a+dx; a+dx<=x&&x<b+(dx/2.0) || a+dx>=x&&x>b-(dx/2.0); x+=dx )
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
		if(dx>0.0)
		{
			for( double x=a; x<b-(dx/2.0); x+=dx )
			{
				integral += dx*(integrand(x)+((integrand(x+dx)-integrand(x))/2.0));
			}
		}else if(dx<0.0)
		{
			for( double x=a; x>b+(dx/2.0); x+=dx )
			{
				integral += dx*(integrand(x)-((integrand(x+dx)-integrand(x))/2.0));
			}
		}else
		{
			//dx should really not be 0
		}
		
		return integral;
	}


	/**
	 * Non-specific integration methods
	 */
	double live_integrate(double(*f)(double), double a, double b, unsigned int p)
	{
		switch(live_integration_method)
		{
		case PHS_INTEGRATION_EULER_FORWARD:
			return integrate_eulerForward(f,a,b,p);
			break;
		case PHS_INTEGRATION_EULER_BACKWARD:
			return integrate_eulerBackward(f,a,b,p);
			break;
		case PHS_INTEGRATION_EULER_TRIANGLES:
			return integrate_eulerTriangles(f,a,b,p);
			break;
		default:
			return 0;
		}
	}

	double cache_integrate(double(*f)(double), double a, double b, unsigned int p)
	{
		switch(cache_integration_method)
		{
		case PHS_INTEGRATION_EULER_FORWARD:
			return integrate_eulerForward(f,a,b,p);
			break;
		case PHS_INTEGRATION_EULER_BACKWARD:
			return integrate_eulerBackward(f,a,b,p);
			break;
		case PHS_INTEGRATION_EULER_TRIANGLES:
			return integrate_eulerTriangles(f,a,b,p);
			break;
		default:
			return 0;
		}
	}

}