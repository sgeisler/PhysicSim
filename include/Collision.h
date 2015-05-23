//
// Created by Sebastian on 23.05.2015.
//

#ifndef PHYSICSIM_COLLISION_H
#define PHYSICSIM_COLLISION_H

#include "Vector.h"
#include <vector>

struct Collision
{
    //list of all intersection points
    std::vector<phs::Vector> pos;

    //collision normal pointing away from collision-tested object
    phs::Vector norm;

    bool isCollision()
    {
        return (pos.size() > 0);
    };
};

#endif //PHYSICSIM_COLLISION_H
