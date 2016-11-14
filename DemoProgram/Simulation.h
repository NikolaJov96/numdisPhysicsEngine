#ifndef SIMULATION_H
#define SIMULATION_H

#include "../ndPE/World.h"

#include "../ndGE/ndGE.h"
#include "../ndGE/Window.h"
#include "../ndGE/Camera.h"

/**
 * Simulation class, which uses ndGE and ndPE to generate example simulation
 */
class Simulation
{
public:
    Simulation();
    ~Simulation();
    void run(); //!< Initializes simulation and run simulation loop
private:
    enum class simState{RUN, STOP}; //!< enum class containing possible simulation states
    void initSystems();         //!< Initializes simulation
    void initShaders();         //!< Loads two shader programs
    void loop();                //!< Main simulation loop
    void processInput();        //!< Update ndGE input manager
    void drawFrame();           //!< Draws next frame to screen
    // void drawHUD(); //
    ndPE::World _world;         //!< ndPE world object that contains all information needed for physics simulation
    ndGE::Window *_window;      //!< ndGE object that contains information about application window
    // input manager            //!< ndGE input manager object
    ndGE::Camera _camera;     //!< ndGE object that controls which part of world will be shown on screen
    // sprite batch             //!< sth we will need for object rendering

    int _scrWidth = 720;        //!< Screen width
    int _scrHeight = 360;       //!< Screen height
    float _fps;                 //!< FPS variable that gets updated after every frame
    simState _runState;         //!< Current simulation state
};

#endif // SIMULATION_H
