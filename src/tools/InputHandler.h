#include "tools/IInputHandler.h"

class InputHandler : public IInputHandler
{
public:
	void handleWindowMove(int xpos, int ypos) override;
	void handleWindowMinimize(bool minimized) override;
	void handleWindowMaximize(bool maximized) override;
	void handleWindowClose() override;
	void handleKey(int key, int scancode, int action, int mods) override;
	void handleMouseButton(int button, int action, int mods) override;
	void handleMousePosition(double xpos, double ypos) override;
	void handleMouseEnterLeave(bool entered) override;
};