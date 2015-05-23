//
// Created by Sebastian on 23.05.2015.
//

#include "Object.h"

std::vector<Shape *> Object::getCollisionBox()
{
    return collisionBox;
}

double Object::getRadius()
{
    double max = 0.0;
    for(std::vector<Shape *>::iterator it = collisionBox.begin(); it != collisionBox.end(); it++)
    {
        if(max < (*it)->getRadius())
        {
            max = (*it)->getRadius();
        }
    }
    return max;
}
