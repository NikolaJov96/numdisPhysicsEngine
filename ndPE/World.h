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
        World(float gravity=0, float amortCoef=1);
        ~World();
        Object *makeObject(GLfloat x, GLfloat y, GLfloat z, GLfloat angle,
                           GLfloat rotx, GLfloat roty, GLfloat rotz, GLfloat scx,
                           GLfloat scy, GLfloat scz, float mass, ObjectTypes type); //!< Adds new object to the world
        std::vector<std::pair<Object*, Object*>> *getCollisions();                  //!< Returns a pointer to vector of pairs of pointers to collided objects
        std::pair<Object*, Object*> *getCollision();                                //!< Returns a pointer to vector of pairs of pointers to collided objects
        void resolveState();                                                        //!< Finds and resolves collisions
        Object *getObject(int ID) const { return _objects[ID]; }                    //!< Get object with desired ID
        int getObjectsNum() { return _objects.size(); }                             //!< Get number of objects
        void makeAStep(float dt);                                                   //!< Updates world state by updating objects states and resolving collisions
        void setGravity(float gravity) { _gravity = gravity; }                      //!< Updates gravity strength
        void setAmortCoef(float amortCoef) { _amortCoef = amortCoef; }              //!< Updates amortization coefficient
    private:
        std::vector<Object*> _objects;      //!< Vector of all objects inside the simulation
        float _gravity;                     //!< Gravity intensity
        float _frameTime;                   //!< Delta time from the las t draw, set bay makeAStep function
        float _amortCoef;
    };

}

#endif // WORLD_H
