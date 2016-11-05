#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace ndGE {

    /**
     * Camera class for 2D simulations
     */
    class Camera2D
    {
    public:
        Camera2D(int screenWidth = 500, int screenHeight = 500);
        ~Camera2D();

        void init(int screenWidth, int screenHeight);   //!<sets up the orthographic matrix and screen dimensions

        void update();                                  //!<updates the camera matrix if needed

        glm::vec2 convertScreenToWorld(glm::vec2 screenCoords); //!< Converts screen to world coordinates

        bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions); //!< Check if box is in view

        /** Set camera position */
        void setPosition(const glm::vec2& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
        /** Set camera scale */
        void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true; }

        /** Get camera position */
        glm::vec2 getPosition() { return _position; }
        /** Get camera scale */
        float getScale() { return _scale; }
        /** Get camera matrix */
        glm::mat4 getCameraMatrix() { return _cameraMatrix; }

    private:
        int _screenWidth;           //!< Screen width
        int _screenHeight;          //!< Screen height
        bool _needsMatrixUpdate;    //!< If some camera properties were changer, matrix will need update
        float _scale;               //!< Camera scale
        glm::vec2 _position;        //!< Camera position
        glm::mat4 _cameraMatrix;    //!< Camera matrix
        glm::mat4 _orthoMatrix;     //!< Camera orthographic matrix
    };

}

#endif // CAMERA2D_H
