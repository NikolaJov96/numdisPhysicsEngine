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
        int getScrW() const;                                    //!< Returns screen width
        int getScrH() const;                                    //!< Returns screen height
        void addShape(const std::string fileName);              //!< Adds new shape from file
        void drawFrame();                                       //!< Draws frame
        void resetTransformMaritces();                          //!< Resets transform matrices for all shapes
        void addTransformMatrix(int objType, GLfloat *data);    //!< Submit transformation matrix for a shape
        ndGE::Camera _camera;   //!< ndGE object that controls which part of world will be shown on screen
    private:
        ShapeDescription loadShape(const std::string &file);    //!< Load shape description form file
        bool checkStatus(GLint objectID,
                         PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
                         PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
                         GLenum statusType);                    //!< Checks fr shader compilation and linking errors
        GLuint installShaders();                                //!< Install shader programs

        int _width;             //!< Screen width
        int _height;            //!< Screen height
        SDL_Window *_window;    //!< SDL window object
        GLuint _programID;      //!< glsl shader program

        /**
         * Structure that is used to encapsulate shape "appearance"
         * openGL information that goes along
         */
        struct Shape
        {
            ShapeDescription *desc = nullptr;       //!< Pointer to shape description
            GLuint vertexBufferID;                  //!< OpenGL vertex buffer id
            GLuint indexBufferID;                   //!< OpenGL index buffer id
            GLuint vertexArrayBufferID;             //!< OpenGL vertex array buffer id
            GLuint transformationMatrixBufferID;    //!< OpenGL buffer id for transformation matrix
        };
        std::vector<std::vector<glm::mat4>> _fullTransforms;    //!< Vector of transform matrix vectors
        std::vector <Shape*> _shapes;                           //!< Vector of shape definitions
        glm::mat4 _projectionMatrix;                            //!< Matrix used to project world to drawing coordinates
    };

}

#endif // WINDOW_H
