#include "include/GContext.h"

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include <iostream>

namespace mouse
{
	bool left=false;
	int x=0, y=0, dx=0, dy=0;
}

sf::Font font;
Vector v(0, 0, 2);
Vector a(1, 1, 1);


GContext::GContext(unsigned int width, unsigned int height, bool fullscreen, sf::ContextSettings cs, unsigned int fps)
{
	sf::Uint32 screenMode = sf::Style::Default;
	if(fullscreen)
		screenMode = sf::Style::Fullscreen;
	window = new sf::RenderWindow(sf::VideoMode(width, height), "Title", screenMode, cs);
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(fps);

	aspectRatio = ((double)width)/((double)height);
	running = true;
	gluquad = gluNewQuadric();
}

GContext::GContext(unsigned int width, unsigned int height, sf::Uint32 sm, sf::ContextSettings cs, unsigned int fps)
{
	window = new sf::RenderWindow(sf::VideoMode(width, height), "Title", sm, cs);
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(fps);

	aspectRatio = ((double)width)/((double)height);
	running = true;
	gluquad = gluNewQuadric();
}


GContext::~GContext(void)
{
	window->~RenderWindow();
}

void GContext::initGL()
{
	glClearColor(COLOR_CLEAR[0], COLOR_CLEAR[1], COLOR_CLEAR[2], COLOR_CLEAR[3]);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	glShadeModel(GL_SMOOTH);
	
	glEnable(GL_NORMALIZE);

	glOrtho(-1,1,-1,1,1,-1);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_COLOR_MATERIAL);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LIGHT_AMBIENT);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
	
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MAT_SHININESS);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MAT_WHITE);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MAT_YELLOW);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MAT_BLACK);
	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	::glLineWidth(2.0);
	//::glPointSize(2.0);
}

void GContext::loopGL()
{
	while(running)
	{
		drawGL(true);
		window->pushGLStates();
		drawSFML();
		window->popGLStates();
		window->display();
		pollEvents();
	}
}

void GContext::drawGL(bool visible)
{
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPerspective(cam.getFOV(), aspectRatio, 0.1, 1000.0);
	
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::gluLookAt(cam);
	//glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
	
	glPushMatrix();
	
	if(visible)
	{
		::glRenderMode(GL_RENDER);
	}else
	{
		::glRenderMode(GL_SELECT);
	}
	/**/
	glInitNames();
	
	glEnable(GL_LIGHTING);
	
	glPushMatrix();
	glTranslated(2,3,-2);
	::glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MAT_OBJECTS);
	glColor4fv(MAT_OBJECTS);
	::gluSphere(gluquad, 1, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-2,1,0);
	::glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MAT_MAGNETIC);
	glColor4fv(MAT_MAGNETIC);
	::gluSphere(gluquad, 0.8, 64, 64);
	glTranslated(6,0,-0.5);
	::glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MAT_ELECTRIC);
	glColor4fv(MAT_ELECTRIC);
	::gluCylinder(gluquad, 0.8, 0.4, 1, 64, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MAT_GRAVITATIONAL);
	glColor4fv(MAT_GRAVITATIONAL);
	::gluDisk(gluquad, 0.4, 0.8, 64, 1);
	::glTranslated(0,0,4);
	glPopMatrix();
	
	//glDisable(GL_LIGHTING);
	
	::glColor4fv(MAT_GRAVITATIONAL);
	::glVector3d(Vector(2.0, 0.0, 0.0));
	::glColor4fv(MAT_MAGNETIC);
	::glVector3d(Vector(0.0, 2.0, 0.0));
	::glColor4fv(MAT_ELECTRIC);
	::glVector3d(Vector(0.0, 0.0, 2.0));
		
	v.rotate(a, 0.01);

	glColor4fv(::MAT_OBJECTS);
	::glVector3d(gluquad, Vector(1,-1,0), v, 24);
	glColor4fv(::MAT_ROTATIONAL);
	::glVector3d(gluquad, Vector(1,-1,0), a, 24);
	glColor4fv(::MAT_NEON_GREEN);
	::glVector3d(gluquad, v+Vector(1,-1,0), (a-v)*2, 24);

	glPushMatrix();
	glColor4fv(MAT_OBJECTS);
	Vector top,bottom,left,right,front,back;
	top = Vector(0,0,1);
	bottom = Vector(0,0,-1);
	left = Vector(0,-1,0);
	right = Vector(0,1,0);
	front = Vector(1,0,0);
	back = Vector(-1,0,0);

	glTranslatev(v);
	glBegin(GL_TRIANGLES);
	::glTriangle(top, front, left, cam.getEYE());
	::glTriangle(top, front, right, cam.getEYE());
	::glTriangle(top, back, right, cam.getEYE());
	::glTriangle(top, back, left, cam.getEYE());
	::glTriangle(bottom, front, left, cam.getEYE());
	::glTriangle(bottom, right, front, cam.getEYE());
	::glTriangle(bottom, back, right, cam.getEYE());
	::glTriangle(bottom, left, back, cam.getEYE());
	glEnd();
	glPopMatrix();
		
	glPushMatrix();
	glTranslatev(v*-1);
	gluCone(0.6, 0.8, 64, true);
	glPopMatrix();
		
	glColor4fv(MAT_TRANSLATIONAL);
	::glVector3d(gluquad, cam.getCENTER(), 24);

	::glPushMatrix();
	float t = 0.2f;
	::glBegin(GL_TRIANGLES);
			
		glColor4f(1.0, 1.0, 1.0, t);
		::glVertex3d(0.0, 0.0, 0.0);
		glColor4f(1.0, 0.0, 0.0, t);
		::glVertex3d(1.0, 0.0, 0.0);
		glColor4f(0.0, 1.0, 0.0, t);
		::glVertex3d(0.0, 1.0, 0.0);
		
		glColor4f(1.0, 1.0, 1.0, t);
		::glVertex3d(0.0, 0.0, 0.0);
		glColor4f(1.0, 0.0, 0.0, t);
		::glVertex3d(1.0, 0.0, 0.0);
		glColor4f(0.0, 0.0, 1.0, t);
		::glVertex3d(0.0, 0.0, 1.0);
		
		glColor4f(1.0, 1.0, 1.0, t);
		::glVertex3d(0.0, 0.0, 0.0);
		glColor4f(0.0, 0.0, 1.0, t);
		::glVertex3d(0.0, 0.0, 1.0);
		glColor4f(0.0, 1.0, 0.0, t);
		::glVertex3d(0.0, 1.0, 0.0);

		glColor4f(1.0, 0.0, 0.0, t);
		::glVertex3d(1.0, 0.0, 0.0);
		glColor4f(0.0, 0.0, 1.0, t);
		::glVertex3d(0.0, 0.0, 1.0);
		glColor4f(0.0, 1.0, 0.0, t);
		::glVertex3d(0.0, 1.0, 0.0);

	::glEnd();
	::glPopMatrix();
	
	::glFlush();
}

void GContext::drawSFML()
{
	sf::CircleShape circle(120);
	circle.setPosition(120,120);
	circle.setFillColor(sf::Color(0,0,0,0));
	circle.setOutlineColor(sf::Color(199, 221, 12, 128));
	circle.setOutlineThickness(10);
	window->draw(circle);

	
}

void GContext::resizeGL(unsigned int width, unsigned int height)
{
	aspectRatio = ((double)width)/((double)height);
	glViewport(0,0,width, height);
	//window->setSize(sf::Vector2u(width, height));
}

void GContext::pollEvents()
{
	mouse::dx = sf::Mouse::getPosition().x - mouse::x;
	mouse::dy = sf::Mouse::getPosition().y - mouse::y;
	mouse::x += mouse::dx;
	mouse::y += mouse::dy;
	
	sf::Event evt;
	while(window->pollEvent(evt))
	{
		if(evt.type == sf::Event::Resized)
		{
			resizeGL(window->getSize().x, window->getSize().y);
		}else if(evt.type == sf::Event::Closed)
		{
			running = false;
		}else if(evt.type == sf::Event::MouseWheelScrolled)
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				cam.zoomFOV(evt.mouseWheelScroll.delta*(-1.0));
			}else
			{
				cam.zoom(evt.mouseWheelScroll.delta*(-1.0));
			}
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		running = false;
	}
	if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		cam.rotateZBound(mouse::dx, mouse::dy, 0.0);
	}
	if(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		cam.translateParallel(mouse::dx, mouse::dy, 0.0);
	}
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mouse::left = true;
	}else if(mouse::left)
	{
		
		mouse::left = false;
		drawGL(false);
	}
}