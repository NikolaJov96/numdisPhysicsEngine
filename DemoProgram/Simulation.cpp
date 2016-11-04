#include <iostream>

#include <SDL2/SDL.h>
#include "GL/glew.h"

#include "Simulation.h"

#include "../ndGE/ndGE.h"
#include "../ndGE/ErrorHandler.h"

Simulation::Simulation() : _scrWidth(720), _scrHeight(360), _fps(0), _runState(RUN) {};

Simulation::~Simulation(){};

void Simulation::run()
{
    std::cout <<"Init Simulation Systems" <<std::endl;
    initSystems();
    std::cout <<"Simulation Loop" <<std::endl;
    loop();
}

void Simulation::initSystems()
{

    ndGE::init();
    _window.create("Sim", _scrWidth, _scrHeight);
    initShaders();
    // init sprite batch
    _camera.init(_scrWidth, _scrHeight);
    _camera.setPosition(glm::vec2(_scrWidth / 2, _scrHeight / 2));

    _world.makeObject(ndPE::ObjectTypes::BALL);
}

void Simulation::loop()
{
    // fps stuff
    // Set previousTicks variable
    // float previousTicks = SDL_GetTicks();
    while (_runState == RUN)
    {
        // Calculate the frameTime in milliseconds
        // float newTicks = SDL_GetTicks();
        // float frameTime = newTicks - previousTicks;
        // previousTicks = newTicks;
        processInput();
        drawFrame();
        // fps stuff
    }
}

void Simulation::initShaders()
{
    std::cout <<"Shaders inited, maybe" <<std::endl;
    // Compile our color shader
    _textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
    _textureProgram.addAttribute("vertexPosition");
    _textureProgram.addAttribute("vertexColor");
    _textureProgram.addAttribute("vertexUV");
    _textureProgram.linkShaders();
}

void Simulation::processInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            _runState = STOP;
            break;
        }
    }
}

void Simulation::drawFrame()
{
    // move to ndGE ! (black magic, proceed with caution!)
/*
    // Set the base depth to 1.0
    glClearDepth(1.0);
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Apply shaderss
    m_textureProgram.use();

    // Draw code goes here
    glActiveTexture(GL_TEXTURE0);

    // Make sure the shader uses texture 0
    GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
    glUniform1i(textureUniform, 0);

    // Grab the camera matrix
    glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
    // Get uniform matrix form shader
    GLint pUniform = m_textureProgram.getUniformLocation("P");
    // Send it back
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    // Draw the background
    m_levels[m_currentLevel]->draw();

    // Begin drawing agents (objects in simulation)
    m_agentSpriteBatch.begin();

    m_grid.draw(m_agentSpriteBatch, m_camera);

    // End spritebatch creation
    m_agentSpriteBatch.end();

    // Render to the screen
    m_agentSpriteBatch.renderBatch();

    // Render the particles
    m_particleEngine.draw(&m_agentSpriteBatch);

    // Render the heads up display (HUD)
    drawHud();

    // Unbind the program
    m_textureProgram.unuse();

    // Swap our buffer and draw everything to the screen!
    m_window.swapBuffer();
    */
}
