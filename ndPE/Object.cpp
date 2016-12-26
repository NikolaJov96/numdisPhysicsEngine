#include "Object.h"

#include <iostream>
#include <glm/glm.hpp>

ndPE::Object::Object(GLfloat x, GLfloat y, GLfloat z, GLfloat angle,
                     GLfloat rotx, GLfloat roty, GLfloat rotz, GLfloat scx,
                     GLfloat scy, GLfloat scz, float mass, ObjectTypes type):
                         _pos(x, y, z), _angle(angle),
                         _rotVec(rotx, roty, rotz),
                         _scaleVec(scx, scy, scz),
                         _velocity(0), _velDir(0, -1, 0),
                         _angVel(0), _angVelVec(0, 1, 0),
                         _mass(mass), _type(type)
{
    oldObj = new Object();
    updateOldInfo();
}

ndPE::Object::~Object(){};

void ndPE::Object::updatePosition(float dt)
{
    glm::vec3 newState = _rotVec * _angle + _angVelVec * _angVel * dt;
    if (glm::length(newState) == 0)
    {
        _angle = 0;
        _rotVec = glm::vec3(0.0f, 1.0f, 0.0f);
    }
    else
    {
        _angle = (glm::length(newState)<360) ? (glm::length(newState)) : (glm::length(newState)-360);
        _rotVec = glm::normalize(newState);
    }
    _pos += _velocity * dt * _velDir;
}
