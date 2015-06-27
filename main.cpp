#include <iostream>
#include <stdio.h>

#include "GContext.h"

int main()
{
    std::cout << "Press [ENTER] to exit the program.\nIronic, isn't it?" << std::endl;

	sf::ContextSettings cs(24, 8, 2, 4, 3, 0);

	GContext gc(1600, 900, false, cs, 60);
	//GContext gc(1600, 900, (sf::Uint32)sf::Style::None, cs, 60);
	//GContext gc(1920, 1080, (sf::Uint32)sf::Style::None, cs, 60);
	//GContext gc(1920, 1080, true, cs, 60);
	gc.window->setTitle("PhysicSim");
	gc.cam.orthogonalize();

	gc.initGL();
	gc.loopGL();
	gc.~GContext();

    return EXIT_SUCCESS;
}
