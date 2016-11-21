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
         * all other attributes needed for transformation matrix
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
            if (velocityVector[0] != 0 || velocityVector[1] != 0 || velocityVector[2] != 0)
            {
                _velocity = glm::length(velocityVector);
                _velDir = glm::normalize(velocityVector);
            }
            else
            {
                _velocity = 0;
                _velDir = glm::vec3(0, -1, 0);
            }
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
            _oldAngle = _angle;
            _oldRotVec = _rotVec;
            _oldVelocity = _velocity;
            _oldVelDir = _velDir;
            _oldAngVel = _angVel;
            _oldAngVelVec = _angVelVec;
        }
        void retrieveOldInfo()                                      //!< Retrieving old data
        {
            _pos = _oldPos;
            _angle = _oldAngle;
            _rotVec = _oldRotVec;
            _velocity = _oldVelocity;
            _velDir = _oldVelDir;
            _angVel = _oldAngVel;
            _angVelVec = _oldAngVelVec;
        }

        friend float findIntersectBB(Object *o1, Object *o2, float dt, float g);   //!< Finds dt in which two ball have collided during the last frame
        friend float findIntersectCB(Object *o1, Object *o2, float dt, float g);   //!< Finds dt in which cube and ball have collided during the last frame
        friend void resolveCollisionBB(Object *o1, Object *o2, float dt, float g); //!< Updates states of collided balls
        friend void resolveCollisionCB(Object *o1, Object *o2, float dt, float g); //!< Updates states of collided cube and ball

        friend bool checkCollision(const Object *o1, const Object *o2);    //!< Determines which collision detection function to call
        friend bool checkCollisionBB(const Object *o1, const Object *o2);  //!< Determines if two ball have collided
        friend bool checkCollisionCC(const Object *o1, const Object *o2);  //!< Determines if two cubes have collided
        friend bool checkCollisionCB(const Object *o1, const Object *o2);  //!< Determines if two cube and ball (respectively) have collided

    private:
        // following 4 lines must remain the same order as listed
        glm::vec3 _pos;         //!< Position vector
        GLfloat _angle;         //!< Angle in degrees
        glm::vec3 _rotVec;      //!< Rotation axis vector (for rendering)
        glm::vec3 _scaleVec;    //!< Object scale in x, y and z axis

        GLfloat _velocity;      //!< Velocity magnitude
        glm::vec3 _velDir;      //!< Velocity direction vector
        GLfloat _angVel;        //!< Angular velocity
        glm::vec3 _angVelVec;   //!< Vector around which object has angular velocity (_angVel)

        glm::vec3 _oldPos;      //!< Position in previous iteration
        GLfloat _oldAngle;      //!< Angle in previous iteration
        glm::vec3 _oldRotVec;   //!< Rotation axis vector (for rendering) in previous iteration

        GLfloat _oldVelocity;   //!< Velocity magnitude in previous iteration
        glm::vec3 _oldVelDir;   //!< Velocity direction vector in previous iteration
        GLfloat _oldAngVel;     //!< Angular velocity in previous iteration
        glm::vec3 _oldAngVelVec;//!< Vector around which object has angular velocity in previous iteration

        float _mass;            //!< Object mass in kg-s
        ObjectTypes _type;      //!< Object type
    };

}

#endif // OBJECT_H
