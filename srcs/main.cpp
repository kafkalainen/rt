#include "../headers/rt.hpp"
#include "../libkaf/glm/glm/vec4.hpp"
#include "../libkaf/glm/glm/mat4x4.hpp"

int main(void)
{
    Application app;

    try
    {
        app.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}