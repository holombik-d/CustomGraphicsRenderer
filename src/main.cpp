#include <memory>
#include "tools/Logger.h"
#include "Window/Window.h"

int main(void)
{
    std::unique_ptr<Window> window = std::make_unique<Window>();

    if(!window->init(640, 480, "Test Window"))
    {
        Logger::log(1, "$s error: Window init error", __FUNCTION__);
        return -1;
    }
    window->mainLoop();
    window->cleanup();
    return 0;
}