#ifndef P2D_MOUSESTATE_HPP
#define P2D_MOUSESTATE_HPP

namespace p2d { namespace input {
    class MouseState {
    public:
        static MouseState* getInstancePtr();
        ~MouseState();
    protected:
        MouseState();

        static MouseState* instancePtr;
    }; // MouseState
} // namespace input
} // namespace p2d

#endif