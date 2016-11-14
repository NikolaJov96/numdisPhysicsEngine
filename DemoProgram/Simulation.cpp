#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Simulation.h"

#include "../ndGE/ndGE.h"
#include "../ndGE/ErrorHandler.h"
#include "../ndGE/Timing.h"

#include "../ndPE/Object.h"
#include "../ndPE/World.h"

ndPE::Object *cubeObj, *ballObj;

Simulation::Simulation() :
    _scrWidth(720),
    _scrHeight(360),
    _fps(0),
    _runState(simState::RUN)
    {};

Simulation::~Simulation(){};

void Simulation::run()
{
    initSystems();
    loop();
}

void Simulation::initSystems()
{
    ndGE::init(); // we'll see
    _window = new ndGE::Window("Sim", _scrWidth, _scrHeight);
    _window->addShape("res/cube.shp");
    _window->addShape("res/ball.shp");

    cubeObj = _world.makeObject(2.0f, 0.0f, -4.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.5f, ndPE::ObjectTypes::CUBE);
    ballObj = _world.makeObject(-2.0f, 0.0f, -4.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, ndPE::ObjectTypes::BALL);
}

void Simulation::loop()
{
    ndGE::FpsLimiter fpsLimiter;                // Create FPS limiter object (with 60 FPS desired FPS value)
    while (_runState == simState::RUN)
    {
        fpsLimiter.begin();                     // Indicate beginning of the iteration to the fpsLimiter
        processInput();                         // Update input manager
        // manually update the world
        cubeObj->setAngle(((int)cubeObj->getAngle() + 1) % 360);
        ballObj->setAngle(((int)ballObj->getAngle() + 1) % 360);
        // world auto update (without collision resolving)
        // get collisions
        // manual collision resolving
        // automatic collision resolving
        drawFrame();                            // Draw next frame

        _fps = fpsLimiter.end();                // Indicate the end of the iteration to the fpsLimiter
        if ((int)cubeObj->getAngle() % 45 == 0) std::cout <<_fps <<std::endl;
    }
}

void Simulation::processInput()
{
    // Update input manager
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            _runState = simState::STOP;
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
                case SDLK_w: _window->_camera.updatePosition(0, 0, -1); break;
                case SDLK_s: _window->_camera.updatePosition(0, 0, 1); break;
                case SDLK_a: _window->_camera.updatePosition(-1, 0, 0); break;
                case SDLK_d: _window->_camera.updatePosition(1, 0, 0); break;
                case SDLK_r: _window->_camera.updatePosition(0, 1, 0); break;
                case SDLK_f: _window->_camera.updatePosition(0, -1, 0); break;
                case SDLK_q: _window->_camera.updateViewDirection(10, 0, 1, 0); break;
                case SDLK_e: _window->_camera.updateViewDirection(-10, 0, 1, 0); break;
            }
            break;
        }
    }
}

void Simulation::drawFrame()
{
    _window->resetTransformMaritces();
    for (int i=0; i<_world.getObjectsNum(); i++)
    {
        ndPE::Object *obj = _world.getObject(i);
        if (obj->getType() == ndPE::ObjectTypes::CUBE) _window->addTransformMatrix(0, obj->getParams());
        if (obj->getType() == ndPE::ObjectTypes::BALL) _window->addTransformMatrix(1, obj->getParams());
    }
    _window->drawFrame();
}
