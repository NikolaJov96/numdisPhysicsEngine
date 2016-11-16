#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace ndGE
{

    /**
     * Class containing information about the camera
     * Enabling it to move through space
     * Returns world to view matrix
     */
    class Camera
    {
    public:
        Camera();
        ~Camera() = default;

        // Get position, view direction and world to view matrix
        glm::vec3 getPosition() const { return _position; }                         //!< Returns camera position
        glm::vec3 getViewDirection() const { return _viewDirection; }               //!< Returns view direction
        glm::mat4 getWorldToViewMatrix() const;                                     //!< Returns world to view transformation matrix

        // Update position
        void updatePosition(GLfloat x, GLfloat y, GLfloat z);                       //!< Update camera position relative to the current position
        void updatePosition(glm::vec3 delta);                                       //!< Update camera position relative to the current position

        // Update position relatively
        void updatePositionRelatively(GLfloat x, GLfloat y, GLfloat z);             //!< Update camera position relative to the current position and view direction
        void updatePositionRelatively(glm::vec3 delta);                             //!< Update camera position relative to the current position and view direction

        // Set position
        void setPosition(GLfloat x, GLfloat y, GLfloat z);                          //!< Set camera position
        void setPosition(glm::vec3 pos);                                            //!< Set camera position

        // Update view direction
        void updateViewDirection(GLfloat deg, GLfloat x, GLfloat y, GLfloat z);     //!< Update camera view direction relative to the current position
        void updateViewDirection(GLfloat deg, glm::vec3 axes);                      //!< Update camera view direction relative to the current position

        // Set view direction
        void setViewDirection(GLfloat x, GLfloat y, GLfloat z);                     //!< Set camera view direction
        void setViewDirection(glm::vec3 dir);                                       //!< Set camera view direction

        // Set (view direction to) look at point
        void setLookAt(GLfloat x, GLfloat y, GLfloat z);                            //!< Set camera look at point
        void setLookAt(glm::vec3 lookAt);                                           //!< Set camera view direction

    private:
        glm::vec3 _position;            //!< Camera position vector
        glm::vec3 _viewDirection;       //!< Camera view direction (always length 1)
        const glm::vec3 UP;             //!< Vector pointing up
    };

}

#endif // CAMERA_H
