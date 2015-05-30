#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <stdio.h>
#include <cmath>

#include "Vector.h"
#include "Tensor.h"
#include "Logger.h"
#include "Integration.h"
//#include "Integration2.h"

using namespace phs;

#define PI 3.14159265358979323846

//Methods declaration
double testIntegrand(double);
Vector testIntegrand(Vector);
Vector accl(Vector);


//Variables declaration
GLFWwindow *gcWindow;
int width=1024, height=512;
Vector c_e(1.0, 3.0, 2.0),
	   c_c(0.0, 0.0, 0.0), 
	   c_u(0.0, 0.0, 1.0);


static void error_callback(int error, const char *description)
{
	fputs(description, stderr);
	_fgetchar();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)  
{
	if ((key == GLFW_KEY_ESCAPE | key == GLFW_KEY_ENTER) && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);  
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		Vector s = c_e.getPerpendicularComponent(Vector(0,0,1));
		s.normalize();
		c_e-=s;
		c_c-=s;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		Vector s = c_e.getPerpendicularComponent(Vector(0,0,1));
		s.normalize();
		c_e+=s;
		c_c+=s;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		Vector s = c_e.getPerpendicularComponent(Vector(0,0,1));
		s.rotate(Vector(0,0,1), 0.5*PI);
		s.normalize();
		c_e-=s;
		c_c-=s;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		Vector s = c_e.getPerpendicularComponent(Vector(0,0,1));
		s.rotate(Vector(0,0,1), -0.5*PI);
		s.normalize();
		c_e-=s;
		c_c-=s;
	}
} 

static void cursor_position_callback(GLFWwindow* window, double x, double y)
{

}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	
}

static void scroll_callback(GLFWwindow* window, double x, double y)
{
	//std::cout << x;
	//std::cout << "  ";
	//std::cout << y << std::endl; 
	c_e*=(1.0-(0.05*y));
}


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
	double a=-2, b=8;
	
	//Vector a, b;
	//a = Vector(0,0,0);
	//b = Vector(4,0,0);
	/*
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
	*/
}

/*void integration2Test()
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
}*/

void functionDrawingTest()
{
	double a=-4, b=4;
	int c = 16;
	double d = (b-a)/c;

	glBegin(GL_LINES);
		glColor3d(0,0.5,1);
		//glVertex3d(a, 0, 0);
		for(double x=a; x<b; x+=d)
		{
			for(double y=a; y<b; y+=d)
			{
				glVertex3d(x, y, testIntegrand(x*x+y*y));
				glVertex3d(x, y+d, testIntegrand(x*x+(y+d)*(y+d)));
				glVertex3d(x+d, y+d, testIntegrand((x+d)*(x+d)+(y+d)*(y+d)));
				glVertex3d(x+d, y, testIntegrand((x+d)*(x+d)+y*y));

				glVertex3d(x, y, testIntegrand(x*x+y*y));
				glVertex3d(x+d, y, testIntegrand((x+d)*(x+d)+y*y));
				glVertex3d(x, y+d, testIntegrand(x*x+(y+d)*(y+d)));
				glVertex3d(x+d, y+d, testIntegrand((x+d)*(x+d)+(y+d)*(y+d)));
			}
		}
		//glVertex3d(b, 0, 0);
	glEnd();
}

double testIntegrand(double x)
{
	//return exp(-0.5*(x*x))/std::sqrt(2*PI);
	return (0.25*x)-4;
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
    //std::cout << "Hello, World!" << std::endl;

	//vectorTest();
	//integrationTest();
	//integration2Test();

	glfwSetErrorCallback(error_callback);
	if(!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	gcWindow = glfwCreateWindow(width, height, "Graphics Context", NULL, NULL);
	if(!gcWindow)
	{
		fprintf(stderr, "Failed to open GLFW Window");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(gcWindow);
	glfwSwapInterval(1);

	glfwSetKeyCallback(gcWindow, key_callback);
	glfwSetCursorPosCallback(gcWindow, cursor_position_callback);
	glfwSetMouseButtonCallback(gcWindow, mouse_button_callback);
	glfwSetScrollCallback(gcWindow, scroll_callback);

	std::cout << "Press [ENTER] to exit the program." << std::endl;
	std::cout << "Ironic, isn't it?" << std::endl;

	while(!glfwWindowShouldClose(gcWindow))
	{
		float ratio;
        int width, height;

        glfwGetFramebufferSize(gcWindow, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        gluPerspective(45, ratio, 1.0, 1000.0);
		gluLookAt(
			c_e.getX(), c_e.getY(), c_e.getZ(),
			c_c.getX(), c_c.getY(), c_c.getZ(),
			c_u.getX(), c_u.getY(), c_u.getZ()
		);
		glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
		glBegin(GL_LINES);
			glColor3d(1,0,0);
			glVertex3d(10, 0, 0);
			glVertex3d(0, 0, 0);
			glColor3d(0,1,0);
			glVertex3d(0, 10, 0);
			glVertex3d(0, 0, 0);
			glColor3d(0,0,1);
			glVertex3d(0, 0, 10);
			glVertex3d(0, 0, 0);
		glEnd();
		glPushMatrix();

		functionDrawingTest();
		glPushMatrix();
		glPopMatrix();

		glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        
		glBegin(GL_TRIANGLES);
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(-0.6f, -0.4f, 0.f);
			glColor3f(0.f, 1.f, 0.f);
			glVertex3f(0.6f, -0.4f, 0.f);
			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
		glPopMatrix();

        glfwSwapBuffers(gcWindow);
        glfwPollEvents();
	}

	glfwDestroyWindow(gcWindow);
	glfwTerminate();

	//std::cout << std::endl << "Press any key to quit." << std::endl;
    //getchar();
    exit(EXIT_SUCCESS);
}
