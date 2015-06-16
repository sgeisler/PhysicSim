#pragma once

#include <SFML\Window.hpp>

class GContext
{
public:
	sf::Window* window;
	
	GContext(unsigned int width, unsigned int height, bool fullscreen, sf::ContextSettings cs);
	virtual ~GContext(void);

	void initGL();
	void loopGL();
	void drawGL(bool);
	void resizeGL(unsigned int, unsigned int);
	void pollEvents();

private:
	bool running;
};
