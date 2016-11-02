#include "Simulation.h"

Simulation::Simulation() : _world(), _window() {};

Simulation::~Simulation() {};

void Simulation::run()
{
    init();
}

void Simulation::init()
{
    _world.makeObject(ndPE::ObjectTypes::BALL);
}
