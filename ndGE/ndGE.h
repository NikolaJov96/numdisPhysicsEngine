#ifndef NDGE_H
#define NDGE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace ndGE {
    extern void init();     //!< Initializes SDL

    struct Vertex
    {
        glm::vec3 position, color;
        Vertex(glm::vec3 p, glm::vec3 c) : position(p), color(c) {};
        Vertex() = default;
    };

    // Structure which contains information about one object (shape)
    struct ShapeData
    {
        Vertex *vertices;
        GLuint numVerts;
        GLushort *indices;
        GLuint numInds;
        ShapeData() : vertices(nullptr), numVerts(0), indices(nullptr), numInds(0) {};
        void cleanup()
        {
            delete [] vertices;
            delete [] indices;
            numVerts = numInds = 0;
        }
        GLsizeiptr vertexBufferSize() const { return numVerts * sizeof(Vertex); }
        GLsizeiptr indexBufferSize() const { return numInds * sizeof(GLushort); }
    };
}

#endif // NDGE_H
