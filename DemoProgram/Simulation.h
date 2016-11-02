#ifndef SIMULATION_H
#define SIMULATION_H

#include "../ndPE/World.h"
#include "../ndGE/Window.h"

class Simulation
{
public:
    Simulation();
    ~Simulation();
    void run();
private:
    void init();
    ndPE::World _world;
    ndGE::Window _window;
};

#endif // SIMULATION_H
