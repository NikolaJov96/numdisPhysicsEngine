#ifndef OBJECT_H
#define OBJECT_H

#include <list>

namespace ndPE {

    enum class ObjectTypes {BALL, PRISM};

    class Object {
    public:
        Object(ObjectTypes type);
        ~Object();
    private:
        int _x, _y;
        ObjectTypes _type;
    };

}

#endif // OBJECT_H
