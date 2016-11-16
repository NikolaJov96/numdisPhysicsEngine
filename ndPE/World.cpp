#include "World.h"

#include <iostream>

ndPE::World::World() : _gravity(0)
{
    std::cout <<"World created" <<std::endl;
};

ndPE::World::~World()
{
    // Free all objects
    while (!_objects.empty())
    {
        delete _objects.back();
        _objects.pop_back();
    }
};

ndPE::Object *ndPE::World::makeObject(GLfloat x, GLfloat y, GLfloat z, GLfloat angle,
                                      GLfloat rotx, GLfloat roty, GLfloat rotz, GLfloat scx,
                                      GLfloat scy, GLfloat scz, float mass, ObjectTypes type)
{
    // Add object and return pointer to it
    _objects.push_back(new Object(x, y, z, angle, rotx, roty, rotz, scx, scy, scz, mass, type));
    return _objects.back();
}

void ndPE::World::makeAStep(float dt)
{
    for (auto &obj : _objects)
    {

    }
}
