#ifndef NDGE_H
#define NDGE_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace ndGE {

    extern void init();                                     //!< Initializes SDL
    extern void fatalError(const std::string &message);     //!< Prints error message, quits SDL and program

    /**
     * Function that converts angle in degrees into angle in
     * radians, only if define CONVERT_TO_RADIANS exists.
     * Different variant i needed for different openGL versions
     */
    #ifdef CONVERT_TO_RADIANS
    inline GLfloat CONV_ANGLE(GLfloat i) { return glm::radians(i); }
    #else
    inline GLfloat CONV_ANGLE(GLfloat i) { return i; }
    #endif // CONVERT_TO_RADIANS

    /**
     * Structure containing information about single vertex
     */
    struct Vertex
    {
        glm::vec3 position, color;      //!< Vectors containing vertex position and color
        Vertex(glm::vec3 p, glm::vec3 c) : position(p), color(c) {};
        Vertex() = default;
    };

    /**
     * Structure containing information about one object (shape)
     */
    struct ShapeDescription
    {
        Vertex *vertices;       //!< Pointer to the array of vertices
        GLuint numVerts;        //!< Number of vertices
        GLushort *indices;      //!< Pointer to the array of indices
        GLuint numInds;         //!< Number of indices
        ShapeDescription() : vertices(nullptr), numVerts(0), indices(nullptr), numInds(0) {};
        void cleanup()
        {
            delete [] vertices;
            delete [] indices;
            numVerts = numInds = 0;
        }
        GLsizeiptr vertexBufferSize() const { return numVerts * sizeof(Vertex); } //!< Returns vertex buffer size in bytes
        GLsizeiptr indexBufferSize() const { return numInds * sizeof(GLushort); } //!< Returns index buffer  size in bytes
    };

}

#endif // NDGE_H
