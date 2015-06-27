#pragma once

#include <SFML/Window.hpp>
#include "GUtils.h"

class GContext
{
public:
	sf::Window* window;
	Camera cam;
	double aspectRatio;
	GLUquadric* gluquad;
	
	GContext(unsigned int width, unsigned int height, bool fullscreen, sf::ContextSettings cs, unsigned int fps);
	GContext(unsigned int width, unsigned int height, sf::Uint32 sm, sf::ContextSettings cs, unsigned int fps);
	virtual ~GContext(void);

	void initGL();
	void loopGL();
	void drawGL(bool);
	void resizeGL(unsigned int, unsigned int);
	void pollEvents();

private:
	bool running;
};
