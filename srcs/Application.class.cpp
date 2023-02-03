#include "../headers/rt.hpp"

void    Application::run() {
    Application::initSfml();
    Application::mainLoop();
    Application::cleanup();
}

void Application::initSfml()
{
    std::cout << "Initialized" << std::endl;
}

void Application::mainLoop()
{
    std::cout << "Loop" << std::endl;
}

void Application::cleanup()
{
    std::cout << "Cleanup" << std::endl;
}