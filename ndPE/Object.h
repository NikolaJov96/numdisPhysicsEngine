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
                GLfloat scy, GLfloat scz, ObjectTypes);
        ~Object();
        /**
         * Returns pointer to the _x, which can be used to access
         * all outher atributes needed for transformation matrix
         */
        GLfloat *getParams() { return &_pos.x; }
        glm::vec3 getPosition() const { return _pos; }              //!< Returns glm::vec3 vector of object position
        GLfloat getAngle() const { return _angle; }                 //!< Returns angel of the object
        glm::vec3 getRotationAxisVector() const { return _rotVec; } //!< Returns glm::vec3 axis vector for object rotation
        glm::vec3 getScaleVector() const { return _scaleVec; }      //!< Returns glm::vec3 vector of object scale
        glm::vec3 getVelocityDirection() const { return _velDir; }  //!< Returns glm::vec3 vector of object velocity direction
        GLfloat getVelocity() const { return _velocity; }           //!< Returns object velocity
        ObjectTypes getType() const { return _type; }               //!< Returns object type

        void setVelocity(GLfloat vel) { _velocity = vel; }          //!< Sets object velocity
        void setPosition(GLfloat x, GLfloat y, GLfloat z)           //!< Sets object position
            { setPosition(glm::vec3(x, y, z)); }
        void setPosition(glm::vec3 pos)                             //!< Sets object position
            { _pos = pos; }
        void setAngle(GLfloat angle) { _angle = angle; }            //!< Set object angle
    private:
        // following 4 lines must remain the same order as listed
        glm::vec3 _pos;         //!< Position vector
        GLfloat _angle;         //!< Angle in degrees
        glm::vec3 _rotVec;      //!< Rotation axis vector
        glm::vec3 _scaleVec;    //!< scale x, y, z
        glm::vec3 _velDir;      //!< Velicity rotation vector
        GLfloat _velocity;      //!< Velocity
        ObjectTypes _type;      //!< Object type
    };

}

#endif // OBJECT_H
