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
    static ShapeDescription loadShape(const std::string &file)
    {
        std::ifstream inFile(file);
        if (!inFile.is_open())
        {
            std::cout <<"Wrong shape file name: " <<file <<std::endl;
            exit(1);
        }
        ShapeDescription ret;
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

ndGE::Window::Window(const std::string &windowName, int width, int height) :
    _width(width), _height(height),
    _projectionMatrix(glm::perspective(glm::radians(60.0f), ((float)width) / height, 0.1f, 30.0f))
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
    glClearColor(0.0f, 0.2f, 0.0f, 1.0f);                                   // Set background color to black
    SDL_GL_SetSwapInterval(0);                                              // Set VSYNC
    glEnable(GL_BLEND);                                                     // Enable alpha blend
    glEnable(GL_DEPTH_TEST);                                                // Enable depth test
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);                      // (needed only for textures)

    _programID = installShaders();                                              // Load, compile and link shaders and return program ID
};

ndGE::Window::~Window(){};

int ndGE::Window::getScrW() const { return _width; }

int ndGE::Window::getScrH() const { return _height; }

void ndGE::Window::addShape(const std::string filePath)
{
    Shape *shape = new Shape();
    shape->desc = new ShapeDescription(loadShape(filePath));

    // Create, bind and allocate vertex buffer
    glGenBuffers(1, &shape->vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, shape->vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, shape->desc->vertexBufferSize(), shape->desc->vertices, GL_DYNAMIC_DRAW);

    // Describe data inside vertex buffer
    glEnableVertexAttribArray(0); // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1); // color (set it using shader)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (char*)(sizeof(GLfloat) * 3));

    // Create, bind and load index buffer
    glGenBuffers(1, &shape->indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape->indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape->desc->indexBufferSize(), shape->desc->indices, GL_DYNAMIC_DRAW);

    // Init buffer for transformation matrix
    glGenBuffers(1, &shape->transformationMatrixBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, shape->transformationMatrixBufferID);
    // Create empty buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4), 0, GL_DYNAMIC_DRAW);

    for (int i=0; i<4; i++)
    {
        glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(GLfloat) * i * 4));
        glEnableVertexAttribArray(i + 2);
        glVertexAttribDivisor(i + 2, 1);
    }

    _shapes.push_back(shape);
    _fullTransforms.push_back(std::vector<glm::mat4>());
}

void ndGE::Window::drawFrame()
{
    // Set the base depth to 1.0
    glClearDepth(1.0);
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (unsigned i=0; i<_shapes.size(); i++)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _shapes[i]->vertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, _shapes[i]->desc->vertexBufferSize(), _shapes[i]->desc->vertices, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0); // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);
        glEnableVertexAttribArray(1); // color (set it using shader)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (char*)(sizeof(GLfloat) * 3));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _shapes[i]->indexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _shapes[i]->desc->indexBufferSize(), _shapes[i]->desc->indices, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, _shapes[i]->transformationMatrixBufferID);
        // Create empty buffer

        for (int i=0; i<4; i++)
        {
            glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(GLfloat) * i * 4));
            glEnableVertexAttribArray(i + 2);
            glVertexAttribDivisor(i + 2, 1);
        }
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4), &_fullTransforms[i][0], GL_DYNAMIC_DRAW);

        glDrawElementsInstanced(GL_TRIANGLES, _shapes[i]->desc->numInds, GL_UNSIGNED_SHORT, 0, _fullTransforms[i].size());
    }

    // Swap our buffer and draw everything to the screen
    SDL_GL_SwapWindow(_window);
}

void ndGE::Window::resetTransformMaritces()
{
    for (unsigned i=0; i<_fullTransforms.size(); i++)
        _fullTransforms[i].clear();
}

void ndGE::Window::addTransformMatrix(int objType, GLfloat *data)
{
    _fullTransforms[objType].push_back(
        _projectionMatrix * _camera.getWorldToViewMatrix() *
        glm::translate(glm::vec3(data[0], data[1], data[2])) *
        glm::rotate(glm::radians(data[3]), glm::vec3(data[4], data[5], data[6])) *
        glm::scale(glm::vec3(data[7], data[8], data[9])));
}
