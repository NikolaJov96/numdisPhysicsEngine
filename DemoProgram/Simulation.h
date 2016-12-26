#ifndef SIMULATION_H
#define SIMULATION_H

#include "../ndPE/World.h"
#include "../ndGE/ndGE.h"
#include "../ndGE/Window.h"
#include "../ndGE/Camera.h"
#include "../ndGE/InputManager.h"

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
    void getInput();            //!< Update ndGE input manager
    void drawFrame();           //!< Draws next frame to screen
    void manualUpdate(int co);  //!< Make changes at the start of every frame
    ndPE::World _world;         //!< ndPE world object that contains all information needed for physics simulation
    ndGE::Window *_window;      //!< ndGE object that contains information about application window
    ndGE::InputManager _input;  //!< ndGE input manager object

    const float CAMERA_TRANSLATION_SPEED = 0.1f;    //!< Camera translation speed in units (meters) per second
    const float CAMERA_ROTATION_SPEED = 2.0f;       //!< Camera rotation speed in degrees per second
    const float MAX_FRAME_TIME = 0.05f;             //!< Maximal time that will be sent to the simulation as a time step

    int _scrWidth = 720;        //!< Screen width
    int _scrHeight = 360;       //!< Screen height
    float _fps;                 //!< FPS variable that gets updated after every frame
    simState _runState;         //!< Current simulation state
};

#endif // SIMULATION_H
