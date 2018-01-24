#include "p2d_mousestate.hpp"

namespace p2d { namespace input {
    MouseState* MouseState::instancePtr = nullptr;

    MouseState* MouseState::getInstancePtr() {
        if (instancePtr == nullptr) {
            instancePtr = new MouseState();
        }

        return instancePtr;
    }

    MouseState::MouseState() {
        ;
    }

    MouseState::~MouseState() {
        delete instancePtr;
    }
} // namespace input
} // namespace p2d