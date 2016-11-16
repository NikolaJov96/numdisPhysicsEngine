#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#include <glm/glm.hpp>

namespace ndGE {

    /**
     * Input manager stores a key map that maps SDL_Keys to booleans.
     * If the value in the key map is true, then the key is pressed.
     * Otherwise, it is released.
     */
    class InputManager
    {
    public:
        InputManager();
        ~InputManager();
        void pressKey(unsigned int keyID);                                  //!< Set key to pressed
        void releaseKey(unsigned int keyID);                                //!< Set key to released
        void setMouseCoords(float x, float y);                              //!< Update mouse coordinates
        bool isKeyDown(unsigned int keyID) const;                           //!< Returns true if the key is held down
        glm::vec2 getMouseCoords() const { return _mouseCoords; }           //!< Get mouse coordinates
        glm::vec2 getPrevMouseCoords() const { return _prevMouseCoords; }   //!< Get mouse coordinates
    private:
        std::unordered_map<unsigned int, bool> _keyMap;                     //!< Map of used keys
        glm::vec2 _mouseCoords, _prevMouseCoords;                           //!< Current mouse coordinates
    };

}

#endif // INPUTMANAGER_H
