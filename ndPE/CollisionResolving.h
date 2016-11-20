#include "Object.h"

namespace ndPE
{
    float findIntersectBB(Object *o1, Object *o2, float frameTime);
    float findIntersectCB(Object *o1, Object *o2, float frameTime);
    void resolveCollisionBB(Object *o1, Object *o2, float frameTime);
    void resolveCollisionCB(Object *o1, Object *o2, float frameTime);
}
