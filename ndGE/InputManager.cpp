#include "InputManager.h"

ndGE::InputManager::InputManager() : _mouseCoords(0.0f), _prevMouseCoords(0.0f) {}
ndGE::InputManager::~InputManager(){}

void ndGE::InputManager::pressKey(unsigned int keyID) {
    _keyMap[keyID] = true;
}

void ndGE::InputManager::releaseKey(unsigned int keyID) {
    _keyMap[keyID] = false;
}

void ndGE::InputManager::setMouseCoords(float x, float y) {
    _prevMouseCoords = _mouseCoords;
    _mouseCoords.x = x;
    _mouseCoords.y = y;
}

bool ndGE::InputManager::isKeyDown(unsigned int keyID) const {
    auto it = _keyMap.find(keyID);
    if (it != _keyMap.end()) return it->second;
    return false;
}
