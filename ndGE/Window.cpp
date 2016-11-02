#include <iostream>

#include "Window.h"

using namespace ndGE;

Window::Window(int w, int h) : _width(w), _hight(h)
{
    std::cout <<"Window created" <<std::endl;
};

Window::~Window(){};
