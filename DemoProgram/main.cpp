#include <iostream>

#include "Simulation.h"
#include <GL/glew.h>

int main(int argc, char *argv[])
{
    std::cout <<"Hello World" <<std::endl;
    Simulation sim;
    sim.run();
    return 0;
}
