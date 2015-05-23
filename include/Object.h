//
// Created by Sebastian on 23.05.2015.
//

#ifndef PHYSICSIM_OBJECT_H
#define PHYSICSIM_OBJECT_H

#include <vector>
#include <memory>

#include "Shape.h"

class Object
{
public:
    std::vector<Shape*> getCollisionBox();
    double getRadius();


private:
    void recalc();

    std::vector<Shape*> collisionBox;
    double radius;

    //TODO: add physical properties
};


#endif //PHYSICSIM_OBJECT_H
