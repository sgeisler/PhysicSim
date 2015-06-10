#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <graphicsUtilities.h>

using namespace glu;

Camera::Camera(double e_x, double e_y, double e_z, double c_x, double c_y, double c_z, double u_x, double u_y, double u_z, double f)
{
	ex = e_x;
	ey = e_y;
	ez = e_z;
	cx = c_x;
	cy = c_y;
	cz = c_z;
	ux = u_x;
	uy = u_y;
	uz = u_z;
	fov = f;
}

