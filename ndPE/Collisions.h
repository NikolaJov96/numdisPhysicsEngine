#include "Object.h"

namespace ndPE
{
    bool checkCollision(const Object *o1, const Object *o2);    //!< Determines which collision detection function to call
    bool checkCollisionBB(const Object *o1, const Object *o2);  //!< Determines if two ball have collided
    bool checkCollisionCC(const Object *o1, const Object *o2);  //!< Determines if two cubes have collided
    bool checkCollisionCB(const Object *o1, const Object *o2);  //!< Determines if two cube and ball (respectively) have collided
}
