#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "ndGE.h"
#include "Window.h"
#include "ErrorHandler.h"

namespace ndGE
{
    static ShapeData loadShape(const std::string &file)
    {
        std::ifstream inFile(file);
        if (!inFile.is_open())
        {
            std::cout <<"Wrong shape file name: " <<file <<std::endl;
            exit(1);
        }
        ShapeData ret;
        inFile >>ret.numVerts >>ret.numInds;
        ret.numInds *= 3;
        std::vector <Vertex> verts;
        for (GLuint i=0; i<ret.numVerts; i++)
        {
            GLfloat x, y, z, r, g, b;
            inFile >>x >>y >>z >>r >>g >>b;
            verts.push_back(Vertex(glm::vec3(x, y, z), glm::vec3(r, g, b)));
        }
        ret.vertices = new Vertex[ret.numVerts];
        memcpy(ret.vertices, &verts[0], ret.numVerts*sizeof(glm::vec3) * 2);
        std::vector <GLushort> inds;
        for (GLuint i=0; i<ret.numInds; i++)
        {
            GLushort x;
            inFile >>x;
            inds.push_back(x);
        }
        ret.indices = new GLushort[ret.numInds];
        memcpy(ret.indices, &inds[0], ret.numInds * sizeof(GLushort));
        return ret;
    }

    static bool checkStatus(GLint objectID,
                 PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
                 PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
                 GLenum statusType)
    {
        GLint status;
        objectPropertyGetterFunc(objectID, statusType, &status);
        if (status != GL_TRUE)
        {
            // Get log length
            GLint infoLogLen;
            objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLen);
            // Get log
            GLchar *buffer = new GLchar[infoLogLen];
            GLsizei bufferSize;
            getInfoLogFunc(objectID, infoLogLen, &bufferSize, buffer);
            std::cout <<buffer <<std::endl;
            delete [] buffer;
            return false;
        }
        return true;
    }

    static GLuint installShaders()
    {
        //Load vertex shader file
        std::stringstream shaderFileBuffer;
        std::ifstream shaderFile("Shaders/vertexShader.vert");
        shaderFileBuffer <<shaderFile.rdbuf();
        std::string vertexShaderCode = shaderFileBuffer.str();
        shaderFile.close();

        // Load fragment  shader file
        shaderFileBuffer.str(std::string());
        shaderFile.open("Shaders/fragmentShader.frag");
        shaderFileBuffer <<shaderFile.rdbuf();
        std::string fragmentShaderCode = shaderFileBuffer.str();
        shaderFile.close();

        // Create shader programs
        GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        // Load shader programs with loaded code
        const GLchar *adapter[1] = {vertexShaderCode.c_str()};
        glShaderSource(vertexShaderID, 1, adapter, 0);
        adapter[0] = fragmentShaderCode.c_str();
        glShaderSource(fragmentShaderID, 1, adapter, 0);

        // Compile shader programs
        glCompileShader(vertexShaderID);
        glCompileShader(fragmentShaderID);

        // Check for errors in vertex shader program compilation
        if (!checkStatus(vertexShaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS)) exit(1);

        // Check for errors in fragment shader program compilation
        if (!checkStatus(fragmentShaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS)) exit(1);

        // Link shader program
        GLuint programID = glCreateProgram();
        glAttachShader(programID, vertexShaderID);
        glAttachShader(programID, fragmentShaderID);
        glLinkProgram(programID);

        // Check for errors in shader program linking
        if (!checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS)) exit(1);

        // Delete shader programs
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

        // Select program to use
        glUseProgram(programID);

        return programID;
    }
}

ndGE::Window::Window(const std::string &windowName, int width, int height) : _width(width), _height(height)
{
    _width = width;
    _height = height;
    _window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, _width,
                               _height, SDL_WINDOW_OPENGL);                 // Open an SL window
    if (_window == nullptr)
        fatalError("SDL Window could not be created!");
    SDL_GLContext glContext = SDL_GL_CreateContext(_window);                // Create OpenGL context
    if (glContext == nullptr)
        fatalError("SDL_GL context could not be created!");
    GLenum error = glewInit();                                              // Setup GLEW
    if (error != GLEW_OK) fatalError("Could not initialize GLEW!");
    std::cout <<"OpenGL version: " <<glGetString(GL_VERSION) <<std::endl;   // Print OpenGL version
    glClearColor(5.0f, 0.0f, 0.0f, 1.0f);                                   // Set background color to black
    SDL_GL_SetSwapInterval(0);                                              // Set VSYNC
    glEnable(GL_BLEND);                                                     // Enable alpha blend
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);                      // (needed only for textures)

    cube = new ShapeData(loadShape("res/cube.shp"));
    ball = new ShapeData(loadShape("res/ball.shp"));

    _programID = installShaders();
};

ndGE::Window::~Window(){};

void ndGE::Window::swapBuffer()
{
    SDL_GL_SwapWindow(_window);     // Swaps previous with newly rendered buffer
}

int ndGE::Window::getScrW() { return _width; }

int ndGE::Window::getScrH() { return _height; }
