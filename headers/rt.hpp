#ifndef RT_HPP
#define RT_HPP

#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "drawer.hpp"

namespace rt {
    using namespace sf;

    class Application {
    public:
        const unsigned int Width = 800;
        const unsigned int Height = 600;
        const sf::Vector2u WindowRect = Vector2u(Width, Height);

        void run();

    private:
        sf::RenderWindow    m_applicationWindow;
        sf::Texture         m_readOnlyTexture;
        sf::Sprite          m_sprite;
        uint8_t             *m_pixelBuffer;
        Drawer              *m_drawer;

        void initSfml();
        void initBuffers();
        void mainLoop();
        void cleanup();
    };
}
#endif