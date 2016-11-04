#include <iostream>
#include "GL/glew.h"

#include "Window.h"
#include "ErrorHandler.h"

ndGE::Window::Window()
{
    std::cout <<"Window object created" <<std::endl;
};

ndGE::Window::~Window(){};

int ndGE::Window::create(std::string windowName, int width, int height)
{
    _width = width;
    _height = height;
    // Open an SL window
    _window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_OPENGL);
    if (_window == nullptr) fatalError("SDL Window could not be created!");
    // Create OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) fatalError("SDL_GL context could not be created!");
    // Set up GLEW
    GLenum error;
    error = glewInit();
    if (error != GLEW_OK) fatalError("Could not initialize GLEW!");
    // Print OpenGL version
    std::cout <<"OpenGL version: " <<glGetString(GL_VERSION) <<std::endl;
    // Set background color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Set VSYNC
    SDL_GL_SetSwapInterval(0);
    // Enable alpha blend
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return 0;
}

void ndGE::Window::swapBuffer()
{
    SDL_GL_SwapWindow(_window);
}
