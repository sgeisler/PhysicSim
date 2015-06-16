#include <iostream>
#include <stdio.h>

#include "GContext.h"

using namespace std;

int main()
{
    cout << "Press [ENTER] to exit the program.\nIronic, isn't it?" << endl;

	GContext gc(1024, 768, false, sf::ContextSettings(24, 8, 0, 4, 3), 60);

	gc.initGL();
	gc.loopGL();

    return EXIT_SUCCESS;
}
