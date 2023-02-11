#include <Raytracer.hpp>
#include <Color.hpp>
#include <string.h>

namespace Raytracer {
    void    Application::run() {
        Application::initSfml();
        Application::initBuffers();
        Application::mainLoop();
        Application::cleanup();
    }

    void Application::initSfml()
    {
        Vector2u windowSize = Vector2u(800, 600);
        m_applicationWindow.create( sf::VideoMode(windowSize), "rt");
        std::cout << "Initialized" << std::endl;
    }

    void Application::initBuffers()
    {
        if (!m_readOnlyTexture.create(WindowRect))
        {
            throw std::exception();
        }

        m_pixelBuffer = (uint8_t*)malloc((sizeof(uint8_t) * Width * Height * 4) + 1);
        if (m_pixelBuffer == nullptr)
        {
            throw std::exception();
        }
        bzero(m_pixelBuffer, (sizeof(uint8_t) * Width * Height * 4));
        m_drawer = new Drawer(m_pixelBuffer, Width, Height);
        m_drawer->setPixel(600, 300, Color(255, 255, 255, 255));
        m_readOnlyTexture.update(m_pixelBuffer);
        m_sprite.setTexture(m_readOnlyTexture);
    }

    void Application::mainLoop()
    {
        std::cout << "Loop" << std::endl;
        while (m_applicationWindow.isOpen())
        {
            sf::Event event;
            while (m_applicationWindow.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    m_applicationWindow.close();
            }

            m_applicationWindow.clear();
            m_applicationWindow.draw(m_sprite);
            m_applicationWindow.display();
        }
    }

    void Application::cleanup()
    {
        free(m_pixelBuffer);
        std::cout << "Cleanup" << std::endl;
    }
};