#include "World.h"

#include <iostream>

#include "Collisions.h"
#include "CollisionResolving.h"

ndPE::World::World(float gravity) : _gravity(gravity)
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
    _frameTime = dt;
    for (auto obj : _objects)
    {
        if (obj->getMass() < 0) continue;
        obj->updateOldInfo();
        obj->setVelocity(obj->getVelocity() + glm::vec3(0.0f, -1.0f, 0.0f) * _gravity * dt);
        obj->updatePosition(dt);
    }
}

std::vector<std::pair<ndPE::Object*, ndPE::Object*>> *ndPE::World::getCollisions()
{
    auto collisions = new std::vector<std::pair<ndPE::Object*, ndPE::Object*>>();
    for (auto o1 = _objects.begin(); o1 != _objects.end(); o1++)
    {
        for (auto o2 = o1 + 1; o2 != _objects.end(); o2++)
        {
            if (ndPE::checkCollision(*o1, *o2))
            {
                collisions->push_back(std::pair<ndPE::Object*, ndPE::Object*>(*o1, *o2));
            }
        }
    }
    return collisions;
}

void ndPE::World::resolveState() // Migrate separate resolving functions to the new file
{
    auto collisions = getCollisions();
    while (collisions->size() > 0)
    {
        // std::cout <<collisions->size() <<"\n";
        for (auto objPair: *collisions)
        {
            ndPE::Object *o1 = objPair.first;
            ndPE::Object *o2 = objPair.second;
            auto o1t = objPair.first->getType();
            auto o2t = objPair.second->getType();
            if (o1t == ndPE::ObjectTypes::BALL && o2t == ndPE::ObjectTypes::CUBE)
            {
                // std::cout <<"B-C" <<std::endl;
                ndPE::resolveCollisionCB(o2, o1, _frameTime, _gravity);
            }
            else if (o1t == ndPE::ObjectTypes::CUBE && o2t == ndPE::ObjectTypes::BALL)
            {
                // std::cout <<"C-B" <<std::endl;
                ndPE::resolveCollisionCB(o1, o2, _frameTime, _gravity);
            }
            else if (o1t == ndPE::ObjectTypes::BALL && o2t == ndPE::ObjectTypes::BALL)
            {
                // std::cout <<"B-B" <<std::endl;
                ndPE::resolveCollisionBB(o1, o2, _frameTime, _gravity);
            }
        }
        delete collisions;
        collisions = getCollisions();
    }
    delete collisions;
}
