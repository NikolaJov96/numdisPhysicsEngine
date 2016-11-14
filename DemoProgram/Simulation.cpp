#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Simulation.h"

#include "../ndGE/ndGE.h"
#include "../ndGE/ErrorHandler.h"
#include "../ndGE/Timing.h"

Simulation::Simulation() :
    _scrWidth(720),
    _scrHeight(360),
    _fps(0),
    _runState(simState::RUN),
    _camera()
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
    _window = new ndGE::Window("Sim", _scrWidth, _scrHeight);  // not sure

    _world.makeObject(ndPE::ObjectTypes::BALL);                     // Create demo object
}

void Simulation::loop()
{
    ndGE::FpsLimiter fpsLimiter;                // Create FPS limiter object (with 60 FPS desired FPS value)
    while (_runState == simState::RUN)
    {
        fpsLimiter.begin();                     // Indicate beginning of the iteration to the fpsLimiter
        processInput();                         // Update input manager
        // manually update the world
        // world auto update (without collision resolving)
        // get collisions
        // manual collision resolving
        // automatic collision resolving
        drawFrame();                            // Draw next frame

        _fps = fpsLimiter.end();                // Indicate the end of the iteration to the fpsLimiter
        std::cout <<_fps <<std::endl;
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
        }
    }
}

void Simulation::drawFrame()
{
    // should be moved to ndGE

    // Set the base depth to 1.0
    glClearDepth(1.0);
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/*
    // Apply shaderss
    _textureProgram.use();

    // Draw code goes here
    glActiveTexture(GL_TEXTURE0);

    // Make sure the shader uses texture 0
    GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
    glUniform1i(textureUniform, 0);

    // Grab the camera matrix
    glm::mat4 projectionMatrix = _camera.getCameraMatrix();
    // Get uniform matrix form shader
    GLint pUniform = _textureProgram.getUniformLocation("P");
    // Send it back
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    // Draw the background
    // _levels[_currentLevel]->draw();

    // Begin drawing agents (objects in simulation)
    _agentSpriteBatch.begin();

    _grid.draw(_agentSpriteBatch, _camera);

    // End spritebatch creation
    _agentSpriteBatch.end();

    // Render to the screen
    _agentSpriteBatch.renderBatch();

    // Render the particles
    _particleEngine.draw(&_agentSpriteBatch);

    // Render the heads up display (HUD)
    drawHud();

    // Unbind the program
    _textureProgram.unuse();
*/
    // Swap our buffer and draw everything to the screen!
    _window->swapBuffer();

}
