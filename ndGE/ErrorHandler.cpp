#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>

#include "ErrorHandler.h"


void ndGE::fatalError(std::string message)
{
    std::cout <<message <<std::endl;
    std::cout <<"Enter any key to quit...";
    std::cin >> message;
    SDL_Quit();
    exit(1);
}
