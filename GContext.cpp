#include "include\GContext.h"

#include <SFML\OpenGL.hpp>
#include <gl\GLU.h>

namespace mouse
{
	int x=0, y=0, dx=0, dy=0;
}

Vector v(1.3, 3.7, 0.539);
	Vector a(1,1,0.3);


GContext::GContext(unsigned int width, unsigned int height, bool fullscreen, sf::ContextSettings cs, unsigned int fps)
{
	sf::Uint32 screenMode = sf::Style::Default;
	if(fullscreen)
		screenMode = sf::Style::Fullscreen;
	window = new sf::Window(sf::VideoMode(width, height), "Title", screenMode, cs);
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(fps);
	aspectRatio = ((double)width)/((double)height);
	running = true;
	gluquad = gluNewQuadric();
}


GContext::~GContext(void)
{
	window->~Window();
}

void GContext::initGL()
{
	::glClearColor(0,0,0,1);
	::glEnable(GL_DEPTH_TEST);
	::glOrtho(-1,1,-1,1,1,-1);
	::glEnable(GL_BLEND);
	::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GContext::loopGL()
{
	v*=0.5;
	while(running)
	{
		drawGL(true);
		pollEvents();
	}
}

void GContext::drawGL(bool visible)
{
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPerspective(cam.getFOV(), aspectRatio, 0.1, 1000);
	
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::gluLookAt(cam);

	glPushMatrix();

	if(visible)
	{
		glColor4d(1,0,0,0.6);
		::glVector3d(gluquad, Vector(2.0, 0.0, 0.0));
		glColor4d(0,1,0,0.6);
		::glVector3d(gluquad, Vector(0.0, 2.0, 0.0));
		glColor4d(0,0,1,0.6);
		::glVector3d(gluquad, Vector(0.0, 0.0, 2.0));
		
		v.rotate(a, 0.01);
		glColor4d(0.8, 0.8, 0.8, 0.25);
		::glVector3d(gluquad, v);
		::glVector3d(gluquad, a);

		::glVector3d(gluquad, cam.getCENTER());

		::glBegin(GL_TRIANGLES);
			
			::glColor4d(1.0, 1.0, 1.0, 0.25);
			::glVertex3d(0.0, 0.0, 0.0);
			::glColor4d(1.0, 0.0, 0.0, 0.25);
			::glVertex3d(1.0, 0.0, 0.0);
			::glColor4d(0.0, 1.0, 0.0, 0.25);
			::glVertex3d(0.0, 1.0, 0.0);
		
			::glColor4d(1.0, 1.0, 1.0, 0.25);
			::glVertex3d(0.0, 0.0, 0.0);
			::glColor4d(1.0, 0.0, 0.0, 0.25);
			::glVertex3d(1.0, 0.0, 0.0);
			::glColor4d(0.0, 0.0, 1.0, 0.25);
			::glVertex3d(0.0, 0.0, 1.0);
		
			::glColor4d(1.0, 1.0, 1.0, 0.25);
			::glVertex3d(0.0, 0.0, 0.0);
			::glColor4d(0.0, 0.0, 1.0, 0.25);
			::glVertex3d(0.0, 0.0, 1.0);
			::glColor4d(0.0, 1.0, 0.0, 0.25);
			::glVertex3d(0.0, 1.0, 0.0);
		
		::glEnd();

		window->display();
	}else
	{
		
	}
}

void GContext::resizeGL(unsigned int width, unsigned int height)
{
	aspectRatio = ((double)width)/((double)height);
	glViewport(0,0,width, height);
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
			cam.zoom(evt.mouseWheelScroll.delta*(-1.0));
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		running = false;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		cam.translateFlat(0,1,0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		cam.translateFlat(1,0,0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		cam.translateFlat(0,-1,0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		cam.translateFlat(-1,0,0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		cam.translateFlat(0,0,1);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		cam.translateFlat(0,0,-1);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		cam.rotateZBound(0,0,1);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		cam.rotateZBound(0,0,-1);
	}
	if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		cam.rotateZBound(mouse::dx, mouse::dy, 0.0);
	}
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		cam.translateParallel(mouse::dx, mouse::dy, 0.0);
	}
}