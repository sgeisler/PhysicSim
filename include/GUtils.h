#pragma once

#include "Vector.h"
#include <SFML\OpenGL.hpp>
#include <gl\GLU.h>

using namespace phs;

class Camera
{
private:
	Vector eye, center, up;
	double fov;

public:
	Camera(double, double, double, double, double, double, double, double, double, double);
	Camera();
	virtual ~Camera(void);

	void rotateZBound(double, double, double);
	void rotateFree(double, double, double);
	void translateFlat(double, double, double);
	void translateParallel(double, double, double);
	inline void zoom(double r){eye*=(1.0+(0.05*r));}
	void orthogonalize();

	inline double getEX()const{return eye.getX()+center.getX();}
	inline double getEY()const{return eye.getY()+center.getY();}
	inline double getEZ()const{return eye.getZ()+center.getZ();}
	inline double getCX()const{return center.getX();}
	inline double getCY()const{return center.getY();}
	inline double getCZ()const{return center.getZ();}
	inline double getUX()const{return up.getX();}
	inline double getUY()const{return up.getY();}
	inline double getUZ()const{return up.getZ();}
	inline Vector getEYE()const{return eye;}
	inline Vector getCENTER()const{return center;}
	inline Vector getUP()const{return up;}
	inline double getFOV()const{return fov;}

};

void gluLookAt(Camera& cam);
void glVertex3d(Vector& v);
void glVector3d(GLUquadric*, Vector&, Vector&);
void glVector3d(GLUquadric*, Vector&);

