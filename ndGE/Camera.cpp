#include "Camera.h"

#include <iostream>

#include "ndGE.h"

 ndGE::Camera::Camera() :
     _position(0.0f, 0.0f, 0.0f),
     _viewDirection(0.0f, 0.0f, -1.0f),
     UP(0.0f, 1.0f, 0.0f)
     {}

glm::mat4 ndGE::Camera::getWorldToViewMatrix() const
{
    // _position + _viewDirection = look at point
    return glm::lookAt(_position, _position + _viewDirection, UP);
}

void ndGE::Camera::updatePosition(GLfloat x, GLfloat y, GLfloat z)
{
     updatePosition(glm::vec3(x, y, z));
}
void ndGE::Camera::updatePosition(glm::vec3 delta)
{
    _position += delta;
}

void ndGE::Camera::updatePositionRelatively(glm::vec3 delta)
{
    updatePositionRelatively(delta.x, delta.y, delta.z);
}
void ndGE::Camera::updatePositionRelatively(GLfloat x, GLfloat y, GLfloat z)
{
    glm::vec3 side = glm::normalize(glm::cross(_viewDirection, UP));    // Horizontal vector normal to view direction
    _position += z * _viewDirection;                                    // Move forwards (backwards)
    _position += x * side;                                              // Move sideways
    _position += y * glm::normalize(glm::cross(side, _viewDirection));  // Move up - down
}

void ndGE::Camera::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
    setPosition(glm::vec3(x, y, z));
}
void ndGE::Camera::setPosition(glm::vec3 pos)
{
    _position = pos;
}

void ndGE::Camera::updateViewDirection(GLfloat deg, GLfloat x, GLfloat y, GLfloat z)
{
    updateViewDirection(deg, glm::vec3(x, y, z));
}
void ndGE::Camera::updateViewDirection(GLfloat deg, glm::vec3 axes)
{
    _viewDirection = glm::normalize(glm::mat3(glm::rotate(CONV_ANGLE(deg), axes)) * _viewDirection);
}

void ndGE::Camera::setViewDirection(GLfloat x, GLfloat y, GLfloat z)
{
    setViewDirection(glm::vec3(x, y, z));
}
void ndGE::Camera::setViewDirection(glm::vec3 dir)
{
    if (glm::length(dir) != 0) _viewDirection = glm::normalize(dir);
}

void ndGE::Camera::setLookAt(GLfloat x, GLfloat y, GLfloat z)
{
    setLookAt(glm::vec3(x, y, z));
}
void ndGE::Camera::setLookAt(glm::vec3 lookAt)
{
    _viewDirection = glm::normalize(lookAt - _position);
}

