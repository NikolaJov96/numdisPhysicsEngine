#include "Object.h"

namespace ndPE
{
    float findIntersectBB(Object *o1, Object *o2, float dt, float g);
    float findIntersectCB(Object *o1, Object *o2, float dt, float g);
    void resolveCollisionBB(Object *o1, Object *o2, float dt, float g);
    void resolveCollisionCB(Object *o1, Object *o2, float dt, float g, float amort);
}
