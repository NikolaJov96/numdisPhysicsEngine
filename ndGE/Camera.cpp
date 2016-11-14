#include <iostream>

#include "Camera.h"

 ndGE::Camera::Camera() :
            position(0.0f, 0.0f, 0.0f),
            viewDirection(0.0f, 0.0f, -1.0f),
            UP(0.0f, 1.0f, 0.0f)
            {}
