#include <iostream>

#include "Object.h"

using namespace ndPE;

Object::Object(ObjectTypes type) : _x(0), _y(0), _type(type)
{
    std::cout <<"Object created" <<std::endl;
};

Object::~Object(){};
