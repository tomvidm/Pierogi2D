#ifndef P2D_MOUSESTATE_HPP
#define P2D_MOUSESTATE_HPP

#include "p2d_mouse.hpp"

namespace p2d { namespace input {
    // This singleton class holds information about the state of
    // the mouse buttons and also provides an interface for easily
    // determining single and double clicks, motion, holding etc.

    #include "p2d_circularbuffer.hpp"
    
    class MouseState {
    public:
        void setMousePosition(const Vector2i& pos);
        void setButtonPressState(const MouseButton& button, const bool& isPressed);
        bool isPressed(const MouseButton& button) const;

        static MouseState* getInstancePtr();
        ~MouseState();
    protected:
        MouseState();

        static MouseState* instancePtr;
    private:
        bool mouseButtonPressed[static_cast<int>(MouseButton::NUM_MOUSE_BUTTONS)];

        unsigned int positionHistorySize = 5;
        Vector2i currentMousePos;

        p2d::utility::CircularBuffer<Vector2i, 10> mousePositionHistory;
    }; // MouseState
} // namespace input
} // namespace p2d

#endif