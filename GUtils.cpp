#include "include\GUtils.h"

#include <SFML\OpenGL.hpp>
#include <gl\GLU.h>

using namespace phs;

Camera::Camera(double ex, double ey, double ez, double cx, double cy, double cz, double ux, double uy, double uz, double f)
{
	eye = Vector(ex,ey,ez);
	center = Vector(cx,cy,cz);
	up = Vector(ux,uy,uz);
	fov = f;
}

Camera::Camera()
{
	eye = Vector(1.0, 4.0, 2.0);
	center = Vector(0.0, 0.0, 0.0);
	up = Vector(0.0, 0.0, 1.0);
	fov = 30;
}

Camera::~Camera(void)
{}

void Camera::orthogonalize()
{
	up = up.getPerpendicularComponent(eye);
	up.normalize();
}

void Camera::rotateZBound(double x, double y, double z)
{
	Vector e_z(0,0,1);
	e_z = up.getParallelComponent(e_z);

	x*=-0.02;
	y*=0.02;
	z*=0.02;

	if(x!=0)
	{
		eye.rotate(e_z, x);
		up.rotate(e_z, x);
	}
	if(y!=0)
	{
		Vector axis = eye.cross(up);
		eye.rotate(axis, y);
		up.rotate(axis, y);
	}
	if(z!=0)
	{
		up.rotate(eye, z);
	}
}

void Camera::rotateFree(double x, double y, double z)
{
	orthogonalize();
	x*=-0.02;
	y*=0.02;
	z*=0.02;

	if(x!=0)
	{
		eye.rotate(up, x);
	}
	if(y!=0)
	{
		Vector axis = eye.cross(up);
		eye.rotate(axis, y);
		up.rotate(axis, y);
	}
	if(z!=0)
	{
		up.rotate(eye, z);
	}
}

void Camera::translateFlat(double x, double y, double z)
{
	x*=-0.02;
	y*=0.02;
	z*=0.02;
	Vector e_z = Vector(0,0,1);
	Vector fwd = eye.getPerpendicularComponent(e_z)*-1.0;
	fwd.normalize();
	Vector right = fwd.cross(e_z);
	center += (right*x + fwd*y + e_z*z);
}

void Camera::translateParallel(double x, double y, double z)
{
	x*=-0.02;
	y*=0.02;
	z*=0.02;
	orthogonalize();
	Vector fwd = eye.getNormalized().getInverted();
	Vector right = fwd.cross(up);
	center += (right*x + up*y + fwd*z);
}

void ::gluLookAt(Camera& cam)
{
	::gluLookAt(
		cam.getEX(), cam.getEY(), cam.getEZ(),
		cam.getCX(), cam.getCY(), cam.getCZ(),
		cam.getUX(), cam.getUY(), cam.getUZ()
	);
}

void glVertex3d(Vector& v)
{
	glVertex3d(v.getX(), v.getY(), v.getZ());
}

void ::glVector3d(GLUquadric* gluQuad, Vector& o, Vector& p)
{
	glPushMatrix();
		glTranslated(o.getX(), o.getY(), o.getZ());
		//if(!(p.getX()==0 & p.getY()==0))
		//{
			Vector axis = p.cross(Vector(0,0,1));
			double angle = std::acos(p.getZ()/p.abs());
			glRotated(180.0, 0.0, 0.0, 1.0);
			glRotated(angle*180/3.14159265359, axis.getX(), axis.getY(), axis.getZ());
		/*}/*else if(p.getZ()<0)
		{
			glRotated(180.0, 1.0, 0.0, 0.0);
		}*/
		glBegin(GL_LINES);
			glVertex3d(0,0,0);
			glVertex3d(0,0,p.abs()*0.85);
		glEnd();
		glTranslated(0.0, 0.0, p.abs()*0.85);
		::gluCylinder(gluQuad, p.abs()*0.05, 0.0, p.abs()*0.15, 4, 1);

	glPopMatrix();
}

void ::glVector3d(GLUquadric* gluQuad, Vector& p)
{
	glPushMatrix();
		//if(!(p.getX()==0 & p.getY()==0))
		//{
			Vector axis = p.cross(Vector(0,0,1));
			double angle = std::acos(p.getZ()/p.abs());
			glRotated(180.0, 0.0, 0.0, 1.0);
			glRotated(angle*180/3.14159265359, axis.getX(), axis.getY(), axis.getZ());
		/*}/*else if(p.getZ()<0)
		{
			glRotated(180.0, 1.0, 0.0, 0.0);
		}*/
		glBegin(GL_LINES);
			glVertex3d(0,0,0);
			glVertex3d(0,0,p.abs()*0.85);
		glEnd();
		glTranslated(0.0, 0.0, p.abs()*0.85);
		::gluCylinder(gluQuad, p.abs()*0.05, 0.0, p.abs()*0.15, 4, 1);
	glPopMatrix();
}

