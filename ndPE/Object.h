#ifndef OBJECT_H
#define OBJECT_H

#include <list>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace ndPE {

    enum class ObjectTypes {BALL, PRISM};

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
        const GLfloat *getParams() const { return &_pos.x; }
        // getters
        glm::vec3 getPosition() const { return _pos; }
        GLfloat getAngle() const { return _angle; }
        glm::vec3 getRotationAxisVector() const { return _rotVec; }
        glm::vec3 getScaleVector() const { return _scaleVec; }
        glm::vec3 getVelocityDirection() const { return _velDir; }
        GLfloat getVelocity() const { return _velocity; }
        ObjectTypes getType() const { return _type; }

        // setters
        void setVelocity(GLfloat vel) { _velocity = vel; }
    private:
        // following 4 lines must remain the same order as listed
        glm::vec3 _pos;         //< Position vector
        GLfloat _angle;         //< Angle in degrees
        glm::vec3 _rotVec;      //< Rotation axis vector
        glm::vec3 _scaleVec;    //< scale x, y, z
        glm::vec3 _velDir;      //< Velicity rotation vector
        GLfloat _velocity;      //< Velocity
        ObjectTypes _type;
    };

}

#endif // OBJECT_H
