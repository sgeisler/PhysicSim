#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "Vector.h"

#define PI 3.14159265358979323846
//#define RADS_PER_DEG 0.0174532925
//#define N_E 2.71828182845904523536

//#define GC 6.67384E-11;

const Vector V_O(0,0,0);
const Vector E_X(1,0,0);
const Vector E_Y(0,1,0);
const Vector E_Z(0,0,1);

const float LIGHT_POSITION[] = {0.0, 0.0, 1.0, 1.0};
const float LIGHT_DIFFUSE[] = {0.75, 0.75, 0.75, 1.0};
const float LIGHT_AMBIENT[] = {0.1, 0.1, 0.1, 1.0};
const float LIGHT_SPECULAR[] = {1.0, 1.0, 1.0, 1.0};

const float COLOR_CLEAR[] = {30.0/255.0, 30.0/255.0, 30.0/255.0, 1.0};

const float MAT_SHININESS[] = {120.0f};

const float MAT_WHITE[] = {1.0, 1.0, 1.0, 1.0};
const float MAT_BLACK[] = {0.0, 0.0, 0.0, 1.0};
const float MAT_RED[] = {1.0, 0.0, 0.0, 1.0};
const float MAT_GREEN[] = {0.0, 1.0, 0.0, 1.0};
const float MAT_BLUE[] = {0.0, 0.0, 1.0, 1.0};
const float MAT_NEON_GREEN[] = {199.0/255.0, 221.0/255.0, 12.0/255.0, 1.0};
const float MAT_YELLOW[] = {255.0/255.0, 198.0/255.0, 0.0/255.0, 1.0};
const float MAT_ORANGE[] = {255.0/255.0, 132.0/255.0, 9.0/255.0, 1.0};

const float MAT_OBJECTS[] = {216.0/255.0, 216.0/255.0, 216.0/255.0, 1.0};
const float MAT_TRANSLATIONAL[] = {209.0/255.0, 136.0/255.0, 217.0/255.0, 1.0};
const float MAT_ROTATIONAL[] = {255.0/255.0, 205.0/255.0, 34.0/255.0, 1.0};
const float MAT_GRAVITATIONAL[] = {210.0/255.0, 82.0/255.0, 82.0/255.0, 1.0};
const float MAT_ELECTRIC[] = {103.0/255.0, 140.0/255.0, 177.0/255.0, 1.0};
const float MAT_MAGNETIC[] = {127.0/255.0, 179.0/255.0, 71.0/255.0, 1.0};
const float MAT_ELECTRIC_ALTERNATIVE[] = {121.0/255.0, 171.0/255.0, 255.0/255.0, 1.0};

const unsigned int COLOR_NEON_GREEN[] = {199, 221, 12, 255};

#endif /*CONSTANTS_H_*/