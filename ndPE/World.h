#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Object.h"

namespace ndPE {

    class World {
    public:
        World();
        ~World();
        Object *makeObject(GLfloat x, GLfloat y, GLfloat z, GLfloat angle,
                           GLfloat rotx, GLfloat roty, GLfloat rotz, GLfloat scx,
                           GLfloat scy, GLfloat scz, ObjectTypes type);
        Object *getObject(int ID) const { return _objects[ID]; }
        int getObjectsNum() { return _objects.size(); }
    private:
        std::vector<Object*> _objects;
        float _gravity;
    };

}

#endif // WORLD_H
