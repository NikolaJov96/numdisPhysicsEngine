#ifndef SIMULATION_H
#define SIMULATION_H

#include "../ndPE/World.h"

#include "../ndGE/ndGE.h"
#include "../ndGE/Window.h"
#include "../ndGE/Camera2D.h"
#include "../ndGE/GLSLProgram.h"

class Simulation
{
public:
    Simulation();
    ~Simulation();
    void run();
private:
    void initSystems();
    void initShaders();
    void drawFrame();
    void loop();
    void processInput();
    // void drawHUD(); ???
    ndPE::World _world;
    ndGE::Window _window;
    ndGE::GLSLProgram _textureProgram;
    // input manager
    ndGE::Camera2D _camera;
    // sprite batch
    // particle engine
    int _scrWidth = 720, _scrHeight = 360;
    float _fps;
    enum {RUN, STOP} _runState;
};

#endif // SIMULATION_H
