#include <iostream>
#include <stdio.h>

#include "GContext.h"

using namespace std;

int main()
{
    cout << "Press [ENTER] to exit the program.\nIronic, isn't it?" << endl;

	GContext gc(600, 480, false, sf::ContextSettings(24, 8, 0, 4, 3));

	gc.initGL();
	gc.loopGL();

    return EXIT_SUCCESS;
}
