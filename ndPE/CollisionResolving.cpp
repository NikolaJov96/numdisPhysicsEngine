#include "CollisionResolving.h"

#include <iostream>
#include <glm/glm.hpp>

#include "Collisions.h"

float ndPE::findIntersectBB(ndPE::Object *o1, ndPE::Object *o2, float dt, float g)
{
    float lt = 0, rt = dt, mt = (rt + lt) / 2;
    bool separated = false;
    while (rt - lt > 0.001f) // Use better measure
    {
        o1->retrieveOldInfo();
        o2->retrieveOldInfo();
        mt = (rt + lt) / 2;
        o1->setVelocity(o1->getVelocity() + glm::vec3(0.0f, -g*mt, 0.0f));
        o2->setVelocity(o2->getVelocity() + glm::vec3(0.0f, -g*mt, 0.0f));
        o1->updatePosition(mt);
        o2->updatePosition(mt);
        separated = !ndPE::checkCollisionBB(o1, o2);
        if (separated) lt = mt;
        else rt = mt;
    }
    o1->retrieveOldInfo();
    o2->retrieveOldInfo();
    o1->setVelocity(o1->getVelocity() + glm::vec3(0.0f, -g*lt, 0.0f));
    o2->setVelocity(o2->getVelocity() + glm::vec3(0.0f, -g*lt, 0.0f));
    o1->updatePosition(lt);
    o2->updatePosition(lt);
    return mt;
}

float ndPE::findIntersectCB(ndPE::Object *o1, ndPE::Object *o2, float dt, float g)
{
    float lt = 0, rt = dt, mt = (rt + lt) / 2;
    bool separated = !ndPE::checkCollisionCB(o1, o2);
    while (rt - lt > 0.001f) // Use better measure
    {
        o2->retrieveOldInfo();
        mt = (rt + lt) / 2;
        o2->setVelocity(o2->getVelocity() + glm::vec3(0.0f, -g*mt, 0.0f));
        o2->updatePosition(mt);
        separated = !ndPE::checkCollisionCB(o1, o2);
        if (separated) lt = mt;
        else rt = mt;
    }
    o2->retrieveOldInfo();
    o2->setVelocity(o2->getVelocity() + glm::vec3(0.0f, -g*lt, 0.0f));
    o2->updatePosition(lt);
    return mt;
}

void ndPE::resolveCollisionBB(ndPE::Object *o1, ndPE::Object *o2, float dt, float g)
{
    float remTime = dt - ndPE::findIntersectBB(o1, o2, dt, g);   // remaining time until end of the frame

    o1->setVelocity(o1->getVelocity() + glm::vec3(0.0f, -g*remTime, 0.0f));
    o2->setVelocity(o2->getVelocity() + glm::vec3(0.0f, -g*remTime, 0.0f));

	glm::vec3 impulseVec = glm::normalize(o1->_pos - o2->_pos) *
        glm::length(o2->getVelocity()*o2->_mass - o1->getVelocity()*o1->_mass); // obj1 impulse

	glm::vec3 newVel1 = o1->getVelocity() + (1 / o1->_mass) * impulseVec;
	glm::vec3 newVel2 = o2->getVelocity() - (1 / o2->_mass) * impulseVec;

	o1->setVelocity(newVel1);
	o2->setVelocity(newVel2);

    /*
    glm::vec3 newRotVec1 = glm::cross(impulseVec, newVel1); // basically, velocity normal component x velocity
    glm::vec3 newRotVec2 = glm::cross(impulseVec, newVel2);
    for (int i = 0; i < 2; ++i) // friction coef should determine how many times to run the loop (i think)
    {
        newRotVec1 += o1->_rotVec;
        newRotVec2 += o2->_rotVec;
    }
    o1->_rotVec = glm::normalize(newRotVec1);
    o2->_rotVec = glm::normalize(newRotVec2);
    */

    o1->updatePosition(remTime);
    o2->updatePosition(remTime);
}

void ndPE::resolveCollisionCB(ndPE::Object *o1, ndPE::Object *o2, float dt, float g)
{
    float remTime = dt - ndPE::findIntersectCB(o1, o2, dt, g);
    o2->setVelocity(o2->getVelocity() + glm::vec3(0.0f, -g*remTime, 0.0f));
    // Opposite vertexes of the cube
    float corns[] = {
        o1->_pos[0] - o1->_scaleVec[0],
        o1->_pos[1] - o1->_scaleVec[1],
        o1->_pos[2] - o1->_scaleVec[2],
        o1->_pos[0] + o1->_scaleVec[0],
        o1->_pos[1] + o1->_scaleVec[1],
        o1->_pos[2] + o1->_scaleVec[2]
        };
    // If center if ball is inside of cube terminate program and request shorter delta time
    // (should be impossible to happen)
    if (o2->_pos[0] > corns[0] && o2->_pos[0] < corns[3] && o2->_pos[1] > corns[1] && o2->_pos[1] < corns[4] &&
        o2->_pos[2] > corns[2] && o2->_pos[2] < corns[5])
        {
            std::cout <<"Center of the ball ended up inside of the cube, destroying the world!" <<std::endl;
            exit(1);
        }

    // If ball collided with the side of the cube
    // front / back
    if (o2->_pos[0] > corns[0] && o2->_pos[0] < corns[3] && o2->_pos[1] > corns[1] && o2->_pos[1] < corns[4] &&
        o2->_pos[2] < corns[2]) o2->setVelocity(o2->getVelocity() * glm::vec3(1.0f, 1.0f, -1.0f));
    else if (o2->_pos[0] > corns[0] && o2->_pos[0] < corns[3] && o2->_pos[1] > corns[1] && o2->_pos[1] < corns[4] &&
        o2->_pos[2] > corns[5]) o2->setVelocity(o2->getVelocity() * glm::vec3(1.0f, 1.0f, -1.0f));
    // top / bottom
    else if (o2->_pos[0] > corns[0] && o2->_pos[0] < corns[3] && o2->_pos[1] < corns[1] &&
        o2->_pos[2] > corns[2] && o2->_pos[2] < corns[5]) o2->setVelocity(o2->getVelocity() * glm::vec3(1.0f, -1.0f, 1.0f));
    else if (o2->_pos[0] > corns[0] && o2->_pos[0] < corns[3] && o2->_pos[1] > corns[4] &&
        o2->_pos[2] > corns[2] && o2->_pos[2] < corns[5]) o2->setVelocity(o2->getVelocity() * glm::vec3(1.0f, -1.0f, 1.0f));
    // left / right
    else if (o2->_pos[0] < corns[0] && o2->_pos[1] > corns[1] && o2->_pos[1] < corns[4] &&
        o2->_pos[2] > corns[2] && o2->_pos[2] < corns[5]) o2->setVelocity(o2->getVelocity() * glm::vec3(-1.0f, 1.0f, 1.0f));
    else if (o2->_pos[0] > corns[3] && o2->_pos[1] > corns[1] && o2->_pos[1] < corns[4] &&
        o2->_pos[2] > corns[2] && o2->_pos[2] < corns[5]) o2->setVelocity(o2->getVelocity() * glm::vec3(-1.0f, 1.0f, 1.0f));

    // If ball collided with the edge of the cube
    // Edges aligned with X axis
    else if (o2->_pos[0] > corns[0] && o2->_pos[0] < corns[3])
    {
        glm::vec3 J = o2->_pos;
        if (o2->_pos[1] < corns[1] && o2->_pos[2] < corns[2]) J -= glm::vec3(o2->_pos[0], corns[1], corns[2]);
        else if (o2->_pos[1] < corns[1] && o2->_pos[2] > corns[5]) J -= glm::vec3(o2->_pos[0], corns[1], corns[5]);
        else if (o2->_pos[1] > corns[4] && o2->_pos[2] < corns[2]) J -= glm::vec3(o2->_pos[0], corns[4], corns[2]);
        else J -= glm::vec3(o2->_pos[0], corns[4], corns[5]);
        J = glm::normalize(J);
        glm::vec3 ballVelocity = o2->getVelocity();
        J = 2 * (ballVelocity[0]*J[0] + ballVelocity[1]*J[1] + ballVelocity[2]*J[2]) * J;
        o2->setVelocity(ballVelocity - J);
    }
    // Edges aligned with Y axis
    else if (o2->_pos[1] > corns[1] && o2->_pos[1] < corns[4])
    {
        glm::vec3 J = o2->_pos;
        if (o2->_pos[0] < corns[0] && o2->_pos[2] < corns[2]) J -= glm::vec3(corns[0], o2->_pos[1], corns[2]);
        else if (o2->_pos[0] < corns[0] && o2->_pos[2] > corns[5]) J -= glm::vec3(corns[0], o2->_pos[1], corns[5]);
        else if (o2->_pos[0] > corns[3] && o2->_pos[2] < corns[2]) J -= glm::vec3(corns[3], o2->_pos[1], corns[2]);
        else J -= glm::vec3(corns[3], o2->_pos[1], corns[5]);
        J = glm::normalize(J);
        glm::vec3 ballVelocity = o2->getVelocity();
        J = 2 * (ballVelocity[0]*J[0] + ballVelocity[1]*J[1] + ballVelocity[2]*J[2]) * J;
        o2->setVelocity(ballVelocity - J);
    }
    // Edges aligned with Z axis
    else if (o2->_pos[2] > corns[2] && o2->_pos[2] < corns[5])
    {
        glm::vec3 J = o2->_pos;
        if (o2->_pos[0] < corns[0] && o2->_pos[1] < corns[1]) J -= glm::vec3(corns[0], corns[1], o2->_pos[2]);
        else if (o2->_pos[0] < corns[0] && o2->_pos[1] > corns[4]) J -= glm::vec3(corns[0], corns[4], o2->_pos[2]);
        else if (o2->_pos[0] > corns[3] && o2->_pos[1] < corns[1]) J -= glm::vec3(corns[3], corns[1], o2->_pos[2]);
        else J -= glm::vec3(corns[3], corns[4], o2->_pos[2]);
        J = glm::normalize(J);
        glm::vec3 ballVelocity = o2->getVelocity();
        J = 2 * (ballVelocity[0]*J[0] + ballVelocity[1]*J[1] + ballVelocity[2]*J[2]) * J;
        o2->setVelocity(ballVelocity - J);
    }

    // If ball position is inside the reach of the corner return true
    else
    {
        glm::vec3 J = o2->_pos;
        if (o2->_pos[0] <= corns[0] && o2->_pos[1] <= corns[1] && o2->_pos[2] <= corns[2]) J -= glm::vec3(corns[0], corns[1], corns[2]);
        else if (o2->_pos[0] <= corns[0] && o2->_pos[1] <= corns[1] && o2->_pos[2] >= corns[5]) J -= glm::vec3(corns[0], corns[1], corns[5]);
        else if (o2->_pos[0] <= corns[0] && o2->_pos[1] >= corns[4] && o2->_pos[2] <= corns[2]) J -= glm::vec3(corns[0], corns[4], corns[2]);
        else if (o2->_pos[0] <= corns[0] && o2->_pos[1] >= corns[4] && o2->_pos[2] >= corns[5]) J -= glm::vec3(corns[0], corns[4], corns[5]);
        else if (o2->_pos[0] >= corns[3] && o2->_pos[1] <= corns[1] && o2->_pos[2] <= corns[2]) J -= glm::vec3(corns[3], corns[1], corns[2]);
        else if (o2->_pos[0] >= corns[3] && o2->_pos[1] <= corns[1] && o2->_pos[2] >= corns[5]) J -= glm::vec3(corns[3], corns[1], corns[5]);
        else if (o2->_pos[0] >= corns[3] && o2->_pos[1] >= corns[4] && o2->_pos[2] <= corns[2]) J -= glm::vec3(corns[3], corns[4], corns[2]);
        else J -= glm::vec3(corns[3], corns[4], corns[5]);
        J = glm::normalize(J);
        glm::vec3 ballVelocity = o2->getVelocity();
        J = 2 * (ballVelocity[0]*J[0] + ballVelocity[1]*J[1] + ballVelocity[2]*J[2]) * J;
        o2->setVelocity(ballVelocity - J);
    }

    // Update position with remaining time
    o2->updatePosition(remTime);
}
