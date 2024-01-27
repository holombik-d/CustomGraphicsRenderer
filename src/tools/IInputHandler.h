// Define an InputHandler class for managing input events

class IInputHandler
{
public:
    virtual void handleWindowMove(int xpos, int ypos) = 0;
    virtual void handleWindowMinimize(bool minimized) = 0;
    virtual void handleWindowMaximize(bool maximized) = 0;
    virtual void handleWindowClose() = 0;
    virtual void handleKey(int key, int scancode, int action, int mods) = 0;
    virtual void handleMouseButton(int button, int action, int mods) = 0;
    virtual void handleMousePosition(double xpos, double ypos) = 0;
    virtual void handleMouseEnterLeave(bool entered) = 0;
};
