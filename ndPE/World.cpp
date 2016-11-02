#include <iostream>

#include "World.h"

using namespace ndPE;

World::World() : _gravity(0)
{
    std::cout <<"World created" <<std::endl;
};

World::~World(){};


void World::makeObject(ObjectTypes type)
{
    _objects.push_back(new Object(type));
}
