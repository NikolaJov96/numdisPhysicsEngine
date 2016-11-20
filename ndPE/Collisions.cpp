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

bool ndPE::checkCollisionCB(const Object *o1, const Object *o2)
{
    glm::vec3 cPos = o1->getPosition();
    glm::vec3 cSca = o1->getScaleVector();
    glm::vec3 bPos = o2->getPosition();
    float rad = o2->getScaleVector()[0];        // Balls will always have same scale in every direction
    if (bPos[0] <= cPos[0] - cSca[0] - rad || bPos[0] >= cPos[0] + cSca[0] + rad) return false;
    if (bPos[1] <= cPos[1] - cSca[1] - rad || bPos[1] >= cPos[1] + cSca[1] + rad) return false;
    if (bPos[2] <= cPos[2] - cSca[2] - rad || bPos[2] >= cPos[2] + cSca[2] + rad) return false;
    return true;
}
