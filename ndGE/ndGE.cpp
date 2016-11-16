#include "ndGE.h"

#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <GL/glew.h>

void ndGE::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);                      // Initialize SDL
    // Initialize GLEW here instead in Window if possible
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);        // Double buffering to avoid flickering
}

void ndGE::fatalError(const std::string &message)
{
    std::cout <<message <<std::endl;
    std::cout <<"Quiting...";
    SDL_Quit();
    exit(1);
}
