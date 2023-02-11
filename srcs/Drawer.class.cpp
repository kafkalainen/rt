//
// Created by joonasvalamaki on 2/3/23.
//

#include "../headers/drawer.hpp"
namespace rt
{
    Drawer::Drawer(uint8_t *buffer, unsigned int width, unsigned int height)
    {
        m_buffer = buffer;
        m_height = height;
        m_width = width;
    }

    void Drawer::setPixel(unsigned int x, unsigned int y, Color color)
    {
        *(m_buffer + (m_width * y + x)) = color.R;
        *(m_buffer + (m_width * y + x + 1)) = color.G;
        *(m_buffer + (m_width * y + x + 2)) = color.B;
        *(m_buffer + (m_width * y + x + 3)) = color.A;
    }
}

