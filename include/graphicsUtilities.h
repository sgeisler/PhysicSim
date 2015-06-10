#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <Vector.h>
#include <Tensor.h>

#include <iostream>
#include <stdio.h>
#include <cmath>

#define CAMERA_FORWARD 0
#define CAMERA_BACKWARD 1
#define CAMERA_LEFT 2
#define CAMERA_RIGHT 3

namespace glu
{	
	
	class Camera
	{
		public:
			Camera(double ex, double ey, double ez, double cx, double cy, double cz, double ux, double uy, double uz, double f);
			~Camera(){};
			inline double getEX(){return ex+cx;}
			inline double getEY(){return ey+cy;}
			inline double getEZ(){return ez+cz;}
			inline double getCX(){return cx;}
			inline double getCY(){return cy;}
			inline double getCZ(){return cz;}
			inline double getUX(){return ux;}
			inline double getUY(){return uy;}
			inline double getUZ(){return uz;}
			inline double getFOV(){return fov;}

			inline void zoom(double d)
			{
				ex *= (1.0-(0.05*d));
				ey *= (1.0-(0.05*d));
				ez *= (1.0-(0.05*d));
			}

			inline void translate(phs::Vector* v)
			{
				cx += v->getX();
				cy += v->getY();
				cz += v->getZ();
			}

			inline void translate(int mode, bool flat, double s)
			{
				phs::Vector v(ex,ey,ez);
				
				if(flat)
				{
					v = v.getPerpendicularComponent(phs::Vector(0,0,1));
					
					if(mode == CAMERA_FORWARD)
					{
						v.invert();
					}else if(mode == CAMERA_LEFT)
					{
						v = v.cross(phs::Vector(0,0,1));
						
					}else if(mode == CAMERA_RIGHT)
					{
						v = v.cross(phs::Vector(0,0,1));
						v.invert();
					}
				}else
				{
					if(mode == CAMERA_FORWARD)
					{
						v.invert();
					}else if(mode == CAMERA_LEFT)
					{
						v = v.cross(phs::Vector(ux,uy,uz));
						
					}else if(mode == CAMERA_RIGHT)
					{
						v = v.cross(phs::Vector(ux,uy,uz));
						v.invert();
					}
				}
				
				v.normalize();
				v*=s;
				translate(&v);
			}

			inline void rotate(double x, double y, double z)
			{
				if(!(x==0 && y==0 && z==0))
				{
					phs::Vector eye(ex,ey,ez);
					phs::Vector up(ux,uy,uz);

					if(x!=0)
					{
						eye.rotate(phs::Vector(0,0,1), x);
						up.rotate(phs::Vector(0,0,1), x);
					}
					if(y!=0)
					{
						eye.rotate(eye.cross(up), y);
						up.rotate(eye.cross(up), y);
					}
					if(z!=0)
					{
						up.rotate(eye.getNormalized(), z);
					}

					ex = eye.getX();
					ey = eye.getY();
					ez = eye.getZ();
					ux = up.getX();
					uy = up.getY();
					uz = up.getZ();
				}
			}
		private:
			double ex,ey,ez,cx,cy,cz,ux,uy,uz;
			double fov;
	};

	inline void vertex(phs::Vector* v)
	{
		glVertex3d(v->getX(), v->getY(), v->getZ());
	}

	inline void lookAt(phs::Vector* eye, phs::Vector* center, phs::Vector* up)
	{
		gluLookAt(
			eye->getX(), eye->getY(), eye->getZ(), 	
			center->getX(), center->getY(), center->getZ(), 	
			up->getX(), up->getY(), up->getZ()	
		);
	}

	inline void lookAt(Camera* cam)
	{
		gluLookAt(
			cam->getEX(), cam->getEY(), cam->getEZ(),	
			cam->getCX(), cam->getCY(), cam->getCZ(),	
			cam->getUX(), cam->getUY(), cam->getUZ()	
		);
	}

	//relative 2D stuff
	static double x2dMin, x2dMax, y2dMin, y2dMax, aspectRatio;
	static double xScl, yScl;
		

	inline void ortho2d(double xLeft, double xRight, double yTop, double yBottom)
	{
		x2dMin = xLeft;
		x2dMax = xRight;
		y2dMin = yTop;
		y2dMax = yBottom;

		xScl = x2dMax-x2dMin;
		yScl = y2dMax-y2dMin;
	}
	
	inline void resizeWindow(double ar)
	{
		aspectRatio = ar;
	}

	inline void vertex2d(double x, double y)
	{
		//x = 2*x/xScl+(-1-2*x2dMin/xScl);
		//y = 2*y/yScl+(-1-2*y2dMin/yScl);
		
		glVertex3d(x*0.062*aspectRatio, y*-0.062, 0);
	}

	inline void prepareMatrix2d(Camera* cam)
	{
		glTranslated(cam->getCX(), cam->getCY(), cam->getCZ());
		//std::cout << cam->getCX() << std::endl;
		
		phs::Vector eye(cam->getEX()-cam->getCX(), cam->getEY()-cam->getCY(), cam->getEZ()-cam->getCZ());
		double angle = std::acos((eye.getZ())/eye.abs());
		phs::Vector axis = eye.cross(phs::Vector(0,0,1));
		//std::cout << angle << std::endl;
		//std::cout << axis.debug("") << std::endl;
		glRotated(angle*180/3.141592, axis.getX()*-1, axis.getY()*-1, axis.getZ()*1);
		
		glTranslated(0, 0, (eye.abs())-0.15);
		
		eye = eye.getPerpendicularComponent(phs::Vector(0,0,1));
		angle = std::acos(eye.getY()/eye.abs());
		if(eye.getX()<0)
		{
			angle *= -1;
		}
		if(cam->getUZ()<0)
		{
			angle+=3.141592;
		}
		glRotated(180-(angle*180/3.141592),0,0,1);
		
	}
	inline void pushMatrix2d()
	{
		glPushMatrix();
	}

}


