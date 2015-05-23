//
// Created by Sebastian on 23.05.2015.
//

#ifndef PHYSICSIM_SHAPE_H
#define PHYSICSIM_SHAPE_H

#include "Collision.h"

class Shape
{
public:
    double getRadius();
    virtual bool isInShape(phs::Vector point);

private:
    virtual void recalc();
    double radius;
};


#endif //PHYSICSIM_SHAPE_H
