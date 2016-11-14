#include <iostream>

#include "World.h"

using namespace ndPE;

World::World() : _gravity(0)
{
    std::cout <<"World created" <<std::endl;
};

World::~World()
{
    while (!_objects.empty())
    {
        delete _objects.back();
        _objects.pop_back();
    }
};

Object *World::makeObject(GLfloat x, GLfloat y, GLfloat z, GLfloat angle,
                        GLfloat rotx, GLfloat roty, GLfloat rotz, GLfloat scx,
                        GLfloat scy, GLfloat scz, ObjectTypes type)
{
    _objects.push_back(new Object(x, y, z, angle, rotx, roty, rotz, scx, scy, scz, type));
    return _objects.back();
}
