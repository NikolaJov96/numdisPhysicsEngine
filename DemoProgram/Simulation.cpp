#include "Simulation.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "../ndPE/Object.h"
#include "../ndGE/Timing.h"


ndPE::Object *ballObj;

Simulation::Simulation() :
    _scrWidth(1000),
    _scrHeight(600),
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

    _world.setGravity(9.81);

    // Should really load object descriptions form file
    // Platform
    _world.makeObject(0.0f, -0.1f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 10.0f, 0.1f, 10.0f, -1.0f, ndPE::ObjectTypes::CUBE);

    // Colliding balls
    ballObj = _world.makeObject(-7.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, ndPE::ObjectTypes::BALL);

    _world.makeObject(2.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, ndPE::ObjectTypes::BALL);
    _world.makeObject(4.0f, 1.0f, 1.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, ndPE::ObjectTypes::BALL);
    _world.makeObject(4.0f, 1.0f, -1.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, ndPE::ObjectTypes::BALL);
    _world.makeObject(6.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, ndPE::ObjectTypes::BALL);
    _world.makeObject(6.0f, 1.0f, 3.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, ndPE::ObjectTypes::BALL);
    _world.makeObject(6.0f, 1.0f, -3.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, ndPE::ObjectTypes::BALL);

    _window->_camera.setPosition(0.0f, 15.0f, 15.0f);
    _window->_camera.setLookAt(0.0f, 0.0f, 2.0f);
}

void Simulation::loop()
{

    ndGE::FpsLimiter fpsLimiter;                        // Create FPS limiter object (with 60 FPS desired FPS value)
    drawFrame();
    int counter = 0;
    while (_runState == simState::RUN)
    {
        fpsLimiter.begin();                             // Indicate beginning of the iteration to the fpsLimiter
        getInput();                                     // Update input manager
        // manually update the world
        manualUpdate(counter);
        // world auto update (without collision resolving)
        float frameTime = fpsLimiter.getDelatTime() / 1000;
        _world.makeAStep(frameTime);                    // automatic collision resolving
        // get collisions
        // manual collision resolving
        // another collision detection and resolving
        _world.resolveState();
        drawFrame();                                    // Draw next frame

        _fps = fpsLimiter.end();                        // Indicate the end of the iteration to the fpsLimiter
        if (++counter % 120 == 0) std::cout <<_fps <<std::endl;
    }
}

void Simulation::getInput()
{
    SDL_Event event;
    int xPos, yPos;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            _runState = simState::STOP;
            break;
        case SDL_KEYDOWN:
            _input.pressKey(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            _input.releaseKey(event.key.keysym.sym);
            break;
        }
    }
    SDL_GetMouseState(&xPos, &yPos);
    _input.setMouseCoords(xPos, yPos);
}

void Simulation::manualUpdate(int co)
{
    // Translate camera
    if (_input.isKeyDown(SDLK_w)) _window->_camera.updatePositionRelatively(0, 0, CAMERA_TRANSLATION_SPEED);
    if (_input.isKeyDown(SDLK_s)) _window->_camera.updatePositionRelatively(0, 0, -CAMERA_TRANSLATION_SPEED);
    if (_input.isKeyDown(SDLK_a)) _window->_camera.updatePositionRelatively(-CAMERA_TRANSLATION_SPEED, 0, 0);
    if (_input.isKeyDown(SDLK_d)) _window->_camera.updatePositionRelatively(CAMERA_TRANSLATION_SPEED, 0, 0);
    if (_input.isKeyDown(SDLK_r)) _window->_camera.updatePositionRelatively(0, CAMERA_TRANSLATION_SPEED, 0);
    if (_input.isKeyDown(SDLK_f)) _window->_camera.updatePositionRelatively(0, -CAMERA_TRANSLATION_SPEED, 0);
    // Rotate camera
    if (_input.isKeyDown(SDLK_j)) _window->_camera.updateViewDirection(CAMERA_ROTATION_SPEED, 0, 1, 0);
    if (_input.isKeyDown(SDLK_l)) _window->_camera.updateViewDirection(-CAMERA_ROTATION_SPEED, 0, 1, 0);
    if (_input.isKeyDown(SDLK_i)) _window->_camera.updateViewDirection(CAMERA_ROTATION_SPEED, 1, 0, 0);
    if (_input.isKeyDown(SDLK_k)) _window->_camera.updateViewDirection(-CAMERA_ROTATION_SPEED, 1, 0, 0);
    // Other updates
    if (co == 240) ballObj->setVelocity(glm::vec3(4.0f, 0.0f, 0.0f));
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
