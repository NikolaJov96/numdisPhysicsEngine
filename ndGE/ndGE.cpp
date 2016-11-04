#include <iostream>
#include <SDL2/SDL.h>
#include "GL/glew.h"

#include "ndGE.h"

void ndGE::init()
{
    std::cout<<"Init ndGE" <<std::endl;
    // Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    // Double buffering to avoid flickering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}
