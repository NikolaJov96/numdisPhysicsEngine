#include "Collisions.h"

#include <iostream>

#include <glm/glm.hpp>

bool ndPE::checkCollision(const ndPE::Object *o1, const ndPE::Object *o2)
{
    ndPE::ObjectTypes o1Type = o1->getType();
    if (o1Type == ndPE::ObjectTypes::CUBE)
    {
        switch (o2->getType())
        {
        case ndPE::ObjectTypes::CUBE:
            return ndPE::checkCollisionCC(o1, o2);
            break;
        case ndPE::ObjectTypes::BALL:
            return ndPE::checkCollisionCB(o1, o2);      // First argument is cube
            break;
        }
    }
    else if (o1Type == ndPE::ObjectTypes::BALL)
    {
        switch (o2->getType())
        {
        case ndPE::ObjectTypes::CUBE:
            return ndPE::checkCollisionCB(o2, o1);      // First argument is cube
            break;
        case ndPE::ObjectTypes::BALL:
            return ndPE::checkCollisionBB(o1, o2);
            break;
        }
    }
    return false;       // This would be very bad
}

bool ndPE::checkCollisionBB(const Object *o1, const Object *o2)
{
    glm::vec3 distVec = o1->getPosition() - o2->getPosition();
    float distSq = distVec[0]*distVec[0] + distVec[1]*distVec[1] + distVec[2]*distVec[2];
    float radSum = o1->getScaleVector()[0] + o2->getScaleVector()[0];
    return radSum * radSum > distSq;
}

bool ndPE::checkCollisionCC(const Object *o1, const Object *o2)
{
    return false;
}

inline static float sqDist(glm::vec3 p1, glm::vec3 p2)
{
    return (p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]) + (p1[2] - p2[2]) * (p1[2] - p2[2]);
}

inline static float sqDist(glm::vec2 p1, glm::vec2 p2)
{
    return (p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]);
}

bool ndPE::checkCollisionCB(const Object *o1, const Object *o2)
{
    // o1 is a cube, o2 is a ball
    // Balls will always have same scale in every direction
    // Cube will always be axis aligned
    float rad = o2->_scaleVec[0], sqRad = rad * rad;
    float corns[] = {
        o1->_pos[0] - o1->_scaleVec[0],
        o1->_pos[1] - o1->_scaleVec[1],
        o1->_pos[2] - o1->_scaleVec[2],
        o1->_pos[0] + o1->_scaleVec[0],
        o1->_pos[1] + o1->_scaleVec[1],
        o1->_pos[2] + o1->_scaleVec[2]
        };

    // If ball position is outside of broad bounding box return false
    if (o2->_pos[0] <= corns[0] - rad || o2->_pos[0] >= corns[3] + rad) return false;
    if (o2->_pos[1] <= corns[1] - rad || o2->_pos[1] >= corns[4] + rad) return false;
    if (o2->_pos[2] <= corns[2] - rad || o2->_pos[2] >= corns[5] + rad) return false;

    // If ball position is inside the reach of the cube side or inside cube itself
    if ((o2->_pos[0] > corns[0] && o2->_pos[0] < corns[3] && o2->_pos[1] > corns[1] && o2->_pos[1] < corns[4] &&
         o2->_pos[2] > corns[2] - rad && o2->_pos[2] < corns[5] + rad) ||

        (o2->_pos[0] > corns[0] && o2->_pos[0] < corns[3] && o2->_pos[1] > corns[1] - rad && o2->_pos[1] < corns[4] + rad &&
        o2->_pos[2] > corns[2] && o2->_pos[2] < corns[5]) ||

        (o2->_pos[0] > corns[0] - rad && o2->_pos[0] < corns[3] + rad && o2->_pos[1] > corns[1] && o2->_pos[1] < corns[4] &&
         o2->_pos[2] > corns[2] && o2->_pos[2] < corns[5])) return true;

    // If ball position is inside the reach of the cube edge return true
    // Edges aligned with X axis
    if (o2->_pos[0] > corns[0] && o2->_pos[0] < corns[3])
        for (int i=1; i<5; i += 3)
            for (int j=2; j<6; j += 3)
                if (sqDist(glm::vec2(o2->_pos[1], o2->_pos[2]), glm::vec2(corns[i], corns[j])) < sqRad) return true;
    // Edges aligned with Y axis
    if (o2->_pos[1] > corns[1] && o2->_pos[1] < corns[4])
        for (int i=0; i<4; i += 3)
            for (int j=2; j<6; j += 3)
                if (sqDist(glm::vec2(o2->_pos[0], o2->_pos[2]), glm::vec2(corns[i], corns[j])) < sqRad) return true;
    // Edges aligned with Z axis
    if (o2->_pos[2] > corns[2] && o2->_pos[2] < corns[5])
        for (int i=0; i<4; i += 3)
            for (int j=1; j<5; j += 3)
                if (sqDist(glm::vec2(o2->_pos[0], o2->_pos[1]), glm::vec2(corns[i], corns[j])) < sqRad) return true;

    // If ball position is inside the reach of the corner return true
    for (int i=0; i<4; i += 3)
        for (int j=1; j<5; j += 3)
            for (int k=2; k<6; k += 3)
                if (sqDist(o2->_pos, glm::vec3(corns[i], corns[j], corns[k])) < sqRad) return true;

    // Else return false
    return false;
}
