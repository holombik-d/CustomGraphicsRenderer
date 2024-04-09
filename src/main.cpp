#include <memory>
#include "ResourceManager.h"
#include "tools/Logger.h"
#include "Window/Window.h"

int main(int argc, char** argv)
{
    ResourceManager::setExecutablePath(argv[0]);

    std::unique_ptr<Window> window = std::make_unique<Window>();
    InputHandler handler;
    if(!window->init(640, 480, "Test Window"))
    {
        Logger::log(1, "$s error: Window init error", __FUNCTION__);
        return -1;
    }

    //ResourceManager::loadShaders("Default", "res/shader/basic.vert", "res/shader/basic.frag");

    if(!window->GetInputHandler())
    {
        window->SetInputHandler(&handler);
    }

    window->mainLoop();
    window->cleanup();

    ResourceManager::unloadAllResources();
    return 0;
}