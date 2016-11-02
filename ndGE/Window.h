#ifndef NDGE_H
#define NDGE_H

namespace ndGE {

    class Window {
    public:
        Window(int w = 720, int h = 360);
        ~Window();
    private:
        int _width, _hight;
    };

}

#endif // NDGE_H
