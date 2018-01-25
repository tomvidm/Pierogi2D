#include "p2d_mousestate.hpp"

namespace p2d { namespace input {
    MouseState* MouseState::instancePtr = nullptr;

    void MouseState::setButtonPressState(const MouseButton& button, const bool& isPressed) {
        mouseButtonPressed[static_cast<int>(button)] = isPressed;
    } // setButtonPressState

    bool MouseState::isPressed(const MouseButton& button) const {
        return mouseButtonPressed[static_cast<int>(button)];
    } // isPressed

    MouseState* MouseState::getInstancePtr() {
        if (instancePtr == nullptr) {
            instancePtr = new MouseState();
        }

        return instancePtr;
    } // getInstancePtr

    MouseState::MouseState() {
        ;
    } // constructor

    MouseState::~MouseState() {
        delete instancePtr;
    } // destructor
} // namespace input
} // namespace p2d