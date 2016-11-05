#include <iostream>

#include "Camera2D.h"

ndGE::Camera2D::Camera2D(int screenWidth, int screenHeight) :
    _screenWidth(screenWidth),
    _screenHeight(screenHeight),
    _needsMatrixUpdate(true),
    _scale(1.0f),
    _position(0.0f, 0.0f),
    _cameraMatrix(1.0f),
    _orthoMatrix(1.0f)
    {}


ndGE::Camera2D::~Camera2D(){}

void ndGE::Camera2D::init(int screenWidth, int screenHeight) {
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
    _orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
}

//updates the camera matrix if needed
void ndGE::Camera2D::update() {

    //Only update if our position or scale have changed
    if (_needsMatrixUpdate) {

        //Camera Translation
        glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
        _cameraMatrix = glm::translate(_orthoMatrix, translate);

        //Camera Scale
        glm::vec3 scale(_scale, _scale, 0.0f);
        _cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

        _needsMatrixUpdate = false;     // Matrix just updated
    }
}

glm::vec2 ndGE::Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {
    screenCoords.y = _screenHeight - screenCoords.y;                    // Invert Y direction
    screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);     // Make it so that 0 is the center
    screenCoords /= _scale;                                             // Scale the coordinates
    screenCoords += _position;                                          // Translate with the camera position
    return screenCoords;
}

// Simple AABB test to see if a box is in the camera view
bool ndGE::Camera2D::isBoxInView(const glm::vec2& position, const glm::vec2& dimensions) {

    glm::vec2 scaledScreenDimensions = glm::vec2(_screenWidth, _screenHeight) / (_scale);

    // The minimum distance before a collision occurs
    const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
    const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

    // Center position of the parameters
    glm::vec2 centerPos = position + dimensions / 2.0f;
    // Center position of the camera
    glm::vec2 centerCameraPos = _position;
    // Vector from the input to the camera
    glm::vec2 distVec = centerPos - centerCameraPos;

    // Get the depth of the collision
    float xDepth = MIN_DISTANCE_X - abs(distVec.x);
    float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

    // If both the depths are > 0, then we collided
    if (xDepth > 0 && yDepth > 0) {
        // There was a collision
        return true;
    }
    return false;
}
