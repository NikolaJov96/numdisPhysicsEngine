#include "Object.h"

#include <iostream>

ndPE::Object::Object(GLfloat x, GLfloat y, GLfloat z, GLfloat angle,
                     GLfloat rotx, GLfloat roty, GLfloat rotz, GLfloat scx,
                     GLfloat scy, GLfloat scz, float mass, ObjectTypes type):
                         _pos(x, y, z), _angle(angle),
                         _rotVec(rotx, roty, rotz),
                         _scaleVec(scx, scy, scz),
                         _velocity(0), _velDir(0, -1, 0),
                         _mass(mass), _type(type)
{
    updateOldInfo();
}

ndPE::Object::~Object(){};

void ndPE::Object::updatePosition(float dt)
{
    /* _angle = int(_angle + _angVel * dt) % 360; */
    _pos += _velocity * dt * _velDir;
}
