#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace ndGE
{

    class Camera
    {
    public:
        Camera() :
            position(0.0f, 0.0f, 0.0f),
            viewDirection(0.0f, 0.0f, -1.0f),
            UP(0.0f, 1.0f, 0.0f)
            {}
        // Get position, view direction and world to view matrix
        glm::vec3 getPosition() const { return position; }
        glm::vec3 getViewDirection() const { return viewDirection; }
        glm::mat4 getWorldToViewMatrix() const
        {
            // position + viewDirection = look at point
            return glm::lookAt(position, position + viewDirection, UP);
        }

        // Update position
        void updatePosition(GLfloat x, GLfloat y, GLfloat z)
            { updatePosition(glm::vec3(x, y, z)); }
        void updatePosition(glm::vec3 delta)
            { position += delta; }
        // Set position
        void setPosition(GLfloat x, GLfloat y, GLfloat z)
            { setPosition(glm::vec3(x, y, z)); }
        void setPosition(glm::vec3 pos)
            { position = pos; }
        // Update view direction
        void updateViewDirection(GLfloat deg, GLfloat x, GLfloat y, GLfloat z)
            { updateViewDirection(deg, glm::vec3(x, y, z)); }
        void updateViewDirection(GLfloat deg, glm::vec3 axes)
            { viewDirection = glm::mat3(glm::rotate(glm::radians(deg), axes)) * viewDirection; }
        // Set view direction
        void setViewDirection(GLfloat x, GLfloat y, GLfloat z)
            { setViewDirection(glm::vec3(x, y, z)); }
        void setViewDirection(glm::vec3 dir)
            { if (glm::length(dir) != 0) viewDirection = glm::normalize(dir); }
        // Set (view direction to) look at point
        void setLookAt(GLfloat x, GLfloat y, GLfloat z)
            { setLookAt(glm::vec3(x, y, z)); }
        void setLookAt(glm::vec3 lookAt)
            { viewDirection = glm::normalize(lookAt - position); }
    private:
        glm::vec3 position;
        glm::vec3 viewDirection; // always length 1
        const glm::vec3 UP;
    };

}
