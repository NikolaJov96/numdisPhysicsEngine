#include <iostream>

#include "Object.h"

using namespace ndPE;

Object::Object(GLfloat x, GLfloat y, GLfloat z, GLfloat angle,
                GLfloat rotx, GLfloat roty, GLfloat rotz, GLfloat scx,
                GLfloat scy, GLfloat scz, ObjectTypes type):
                _pos(x, y, z), _angle(angle),
                _rotVec(rotx, roty, rotz),
                _scaleVec(scx, scy, scz),
                _velocity(0), _type(type)
                {}

Object::~Object(){};



























