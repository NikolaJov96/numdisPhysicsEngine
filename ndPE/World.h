#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Object.h"

namespace ndPE {

    /**
     * Class that contains needed information about world and objects
     */
    class World {
    public:
        World();
        ~World();
        Object *makeObject(GLfloat x, GLfloat y, GLfloat z, GLfloat angle,
                           GLfloat rotx, GLfloat roty, GLfloat rotz, GLfloat scx,
                           GLfloat scy, GLfloat scz, ObjectTypes type);             //!< Adds new object to the world
        Object *getObject(int ID) const { return _objects[ID]; }                    //!< Get object with desired ID
        int getObjectsNum() { return _objects.size(); }                             //!< Get number of objects
    private:
        std::vector<Object*> _objects;      //!< Vector of all objects inside the simulation
        float _gravity;                     //!<
    };

}

#endif // WORLD_H
