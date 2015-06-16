#include "include\GContext.h"

#include <SFML\OpenGL.hpp>
#include <gl\GLU.h>

GContext::GContext(unsigned int width, unsigned int height, bool fullscreen, sf::ContextSettings cs)
{
	sf::Uint32 screenMode = sf::Style::Default;
	if(fullscreen)
		screenMode = sf::Style::Fullscreen;
	window = new sf::Window(sf::VideoMode(width, height), "Title", screenMode, cs);
	running = true;
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
	while(running)
	{
		drawGL(true);
		pollEvents();
	}
}

void GContext::drawGL(bool visible)
{
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(visible)
	{
		::glBegin(GL_TRIANGLES);
			::glColor4d(1.0, 1.0, 1.0, 0.5);
			::glVertex3d(0.0, 0.0, 0.0);
			::glColor4d(0.0, 0.5, 1.0, 0.5);
			::glVertex3d(0.0, 1.0, 0.0);
			::glColor4d(1.0, 0.5, 0.0, 0.5);
			::glVertex3d(1.0, 0.0, 0.0);
		::glEnd();

		window->display();
	}else
	{
		
	}
}

void GContext::resizeGL(unsigned int width, unsigned int height)
{

}

void GContext::pollEvents()
{
	sf::Event evt;
	while(window->pollEvent(evt))
	{
		if(evt.type == sf::Event::Resized)
		{
			resizeGL(window->getSize().x, window->getSize().y);
		}else if(evt.type == sf::Event::Closed)
		{
			running = false;
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		running = false;
	}
}