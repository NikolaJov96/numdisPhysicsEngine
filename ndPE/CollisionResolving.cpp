#include "CollisionResolving.h"

#include <iostream>
#include <glm/glm.hpp>

#include "Collisions.h"

float ndPE::findIntersectBB(ndPE::Object *o1, ndPE::Object *o2, float frameTime)
{
    float lt = 0, rt = frameTime, mt = (rt + lt) / 2;
    bool separated = !ndPE::checkCollisionBB(o1, o2);
    while (rt - lt > 0.0001f || !separated) // Use better measure
    {
        // std::cout <<lt <<" " <<rt <<" " <<separated <<std::endl;
        o1->retrieveOldInfo();
        o2->retrieveOldInfo();
        mt = (rt + lt) / 2;
        o1->updatePosition(mt);
        o2->updatePosition(mt);
        separated = !ndPE::checkCollisionBB(o1, o2);
        if (separated) lt = mt;
        else rt = mt;
    }
    // std::cout <<separated <<std::endl;
    o1->updateOldInfo();
    o2->updateOldInfo();
    return mt;
}

float ndPE::findIntersectCB(ndPE::Object *o1, ndPE::Object *o2, float frameTime)
{
    return 0;
}

void ndPE::resolveCollisionBB(ndPE::Object *o1, ndPE::Object *o2, float frameTime)
{
    float remTime = frameTime - ndPE::findIntersectBB(o1, o2, frameTime);   // remaining time untile end of the frame

    // Zasto impulseVec mnozis sa o1->_mass ???
	glm::vec3 impulseVec = glm::normalize(o1->_pos - o2->_pos) * glm::length(o2->getVelocity()*o2->_mass - o1->getVelocity()*o1->_mass); // obj1 impulse
	glm::vec3 newVel1 = o1->getVelocity() + (1 / o1->_mass) * impulseVec;
	glm::vec3 newVel2 = o2->getVelocity() - (1 / o2->_mass) * impulseVec;

	// std::cout <<impulseVec[0] <<" " <<impulseVec[1] <<" " <<impulseVec[2] <<"\n";

    // std::cout <<o1->getVelocity()[0] <<" " <<o1->getVelocity()[1] <<" " <<o1->getVelocity()[2] <<std::endl;
    // std::cout <<o1->getPosition()[0] <<" " <<o1->getPosition()[1] <<" " <<o1->getPosition()[2] <<std::endl;
    // std::cout <<o2->getVelocity()[0] <<" " <<o2->getVelocity()[1] <<" " <<o2->getVelocity()[2] <<std::endl;
    // std::cout <<o2->getPosition()[0] <<" " <<o2->getPosition()[1] <<" " <<o2->getPosition()[2] <<std::endl <<std::endl;

	o1->setVelocity(newVel1);
	o2->setVelocity(newVel2);
    o1->updatePosition(remTime);
    o2->updatePosition(remTime);

    // std::cout <<newVel1[0] <<" " <<newVel1[1] <<" " <<newVel1[2] <<std::endl;
    // std::cout <<o1->getPosition()[0] <<" " <<o1->getPosition()[1] <<" " <<o1->getPosition()[2] <<std::endl;
    // std::cout <<newVel2[0] <<" " <<newVel2[1] <<" " <<newVel2[2] <<std::endl;
    // std::cout <<o2->getPosition()[0] <<" " <<o2->getPosition()[1] <<" " <<o2->getPosition()[2] <<std::endl;
}

void ndPE::resolveCollisionCB(ndPE::Object *o1, ndPE::Object *o2, float frameTime)
{
    o2->setVelocity(o2->getVelocity() * glm::vec3(1.0f, -1.0f, 1.0f));
    o2->updatePosition(frameTime);
}
