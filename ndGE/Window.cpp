#include <iostream>

#include "GL/glew.h"

#include "Window.h"
#include "ErrorHandler.h"

ndGE::Window::Window(const std::string &windowName, int width, int height) : _width(width), _height(height)
{
    _width = width;
    _height = height;
    _window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, _width,
                               _height, SDL_WINDOW_OPENGL);                 // Open an SL window
    if (_window == nullptr)
        fatalError("SDL Window could not be created!");
    SDL_GLContext glContext = SDL_GL_CreateContext(_window);                // Create OpenGL context
    if (glContext == nullptr)
        fatalError("SDL_GL context could not be created!");
    GLenum error = glewInit();                                              // Setup GLEW
    if (error != GLEW_OK) fatalError("Could not initialize GLEW!");
    std::cout <<"OpenGL version: " <<glGetString(GL_VERSION) <<std::endl;   // Print OpenGL version
    glClearColor(5.0f, 0.0f, 0.0f, 1.0f);                                   // Set background color to black
    SDL_GL_SetSwapInterval(0);                                              // Set VSYNC
    glEnable(GL_BLEND);                                                     // Enable alpha blend
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);                      // (needed only for textures)
};

ndGE::Window::~Window(){};

void ndGE::Window::swapBuffer()
{
    SDL_GL_SwapWindow(_window);     // Swaps previous with newly rendered buffer
}

int ndGE::Window::getScrW() { return _width; }

int ndGE::Window::getScrH() { return _height; }
