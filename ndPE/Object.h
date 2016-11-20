#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace ndPE {

    enum class ObjectTypes {CUBE, BALL};    //!< Supported object types

    /**
     * Class that contains all of the information about
     * and manipulates single object inside the world
     */
    class Object {
    public:
        Object(GLfloat x, GLfloat y, GLfloat z, GLfloat angle,
                GLfloat rotx, GLfloat roty, GLfloat rotz, GLfloat scx,
                GLfloat scy, GLfloat scz, float mass, ObjectTypes);
        ~Object();
        /**
         * Returns pointer to the _x, which can be used to access
         * all outher atributes needed for transformation matrix
         */
        GLfloat *getParams() { return &_pos.x; }
        glm::vec3 getPosition() const { return _pos; }              //!< Returns glm::vec3 vector of object position
        GLfloat getAngle() const { return _angle; }                 //!< Returns angel of the object in degrees
        glm::vec3 getRotationAxisVector() const { return _rotVec; } //!< Returns glm::vec3 axis vector for object rotation
        glm::vec3 getScaleVector() const { return _scaleVec; }      //!< Returns glm::vec3 vector of object scale
        glm::vec3 getVelocityDirection() const { return _velDir; }  //!< Returns glm::vec3 vector of object velocity direction
        GLfloat getVelocityMagnitude() const { return _velocity; }  //!< Returns object velocity magnitude
        glm::vec3 getVelocity() const {return _velocity * _velDir;} //!< Returns velocity vector
        float getMass() const { return _mass; }                     //!< Returns object's mass
        ObjectTypes getType() const { return _type; }               //!< Returns object type

        void setVelocity(glm::vec3 velocityVector)                  //!< Sets object velocity
        {
            _velocity = glm::length(velocityVector);
            _velDir = glm::normalize(velocityVector);
        }
        void setPosition(GLfloat x, GLfloat y, GLfloat z)           //!< Sets object position
            { setPosition(glm::vec3(x, y, z)); }
        void setPosition(glm::vec3 pos)                             //!< Sets object position
            { _pos = pos; }
        void setAngle(GLfloat angle) { _angle = angle; }            //!< Set object angle
        void updatePosition(float dt);                              //!< Update object's position
        void updateOldInfo()                                        //!< Current position and velocity becomes "old"
        {
            _oldPos = _pos;
            _oldVelDir = _velDir;
            _oldVelocity = _velocity;
        }

        friend float findIntersectBB(Object *o1, Object *o2);
        friend float findIntersectCB(Object *o1, Object *o2);
        friend void resolveCollisionBB(Object *o1, Object *o2, glm::vec3 intersectPoint);
        friend void resolveCollisionCB(Object *o1, Object *o2, glm::vec3 intersectPoint);

    private:
        // following 4 lines must remain the same order as listed
        glm::vec3 _pos;         //!< Position vector
        GLfloat _angle;         //!< Angle in degrees
        glm::vec3 _rotVec;      //!< Rotation axis vector
        glm::vec3 _scaleVec;    //!< scale x, y, z
        glm::vec3 _velDir;      //!< Velocity direction vector
        GLfloat _velocity;      //!< Velocity magnitude
        GLfloat _oldVelocity;   //!< Velocity magnitude in prevous iteration
        glm::vec3 _oldVelDir;   //!< Velocity direction in previous iteration
        glm::vec3 _oldPos;      //!< Position in previous iteration
        float _mass;            //!< Object mass in kg-s
        ObjectTypes _type;      //!< Object type
    };

}

#endif // OBJECT_H
