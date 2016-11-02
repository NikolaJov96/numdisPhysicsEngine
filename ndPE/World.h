#ifndef WORLD_H
#define WORLD_H

#include <list>

#include "Object.h"

namespace ndPE {

    class World {
    public:
        World();
        ~World();
        void makeObject(ObjectTypes type);
    private:
        std::list<Object*> _objects;
        float _gravity;
    };

}

#endif // WORLD_H
