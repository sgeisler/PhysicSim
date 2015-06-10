#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <Vector.h>
#include <Tensor.h>

#define CAMERA_FORWARD (int)0
#define CAMERA_BACKWARD (int)1
#define CAMERA_LEFT (int)2
#define CAMERA_RIGHT (int)3

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
			inline double getFOV(){return fov;};

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

}
