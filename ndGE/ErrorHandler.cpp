#include <cstdlib>
#include <iostream>

#include <SDL2/SDL.h>

#include "ErrorHandler.h"

void ndGE::fatalError(const std::string &message)
{
    std::cout <<message <<std::endl;
    std::cout <<"Quiting...";
    SDL_Quit();
    exit(1);
}
