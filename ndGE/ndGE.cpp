#include <iostream>

#include <SDL2/SDL.h>
#include "GL/glew.h"

#include "ndGE.h"
#include "ErrorHandler.h"

void ndGE::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);                                          // Initialize SDL
    // Initialize GLEW here instead in Window if possible
    std::cout <<"OpenGL version: " <<glGetString(GL_VERSION) <<std::endl;   // Print OpenGL version
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);                            // Double buffering to avoid flickering
}
