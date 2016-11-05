#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <SDL2/SDL.h>

namespace ndGE {

    /**
     * Class that contains information about application window
     */
    class Window {
    public:
        Window(const std::string &windowName, int width, int height);
        ~Window();
        void swapBuffer();      //!< Swaps image currently displayed with the newly rendered
        int getScrW();          //!< Returns screen width
        int getScrH();          //!< Returns screen height
    private:
        int _width;             //!< Screen width
        int _height;            //!< Screen height
        SDL_Window *_window;    //!< SDL window object
    };

}

#endif // WINDOW_H
