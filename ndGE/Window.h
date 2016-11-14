#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "ndGE.h"
#include "Camera.h"

namespace ndGE {

    /**
     * Class that contains information about application window
     */
    class Window {
    public:
        Window(const std::string &windowName, int width, int height);
        ~Window();
        int getScrW() const;    //!< Returns screen width
        int getScrH() const;    //!< Returns screen height
        void addShape(const std::string fileName);
        void drawFrame();       //!< Draws frame
        void resetTransformMaritces();
        void addTransformMatrix(int objType, GLfloat *data);
        ndGE::Camera _camera;   //!< ndGE object that controls which part of world will be shown on screen
    private:
        int _width;             //!< Screen width
        int _height;            //!< Screen height
        SDL_Window *_window;    //!< SDL window object
        GLuint _programID;      //!< glsl shader program

        struct Shape
        {
            ShapeDescription *desc = nullptr;
            GLuint vertexBufferID, indexBufferID, transformationMatrixBufferID;
        };
        std::vector <Shape*> _shapes; //!< Cube and ball definitions
        std::vector<std::vector <glm::mat4>> _fullTransforms;
        glm::mat4 _projectionMatrix;
    };

}

#endif // WINDOW_H
