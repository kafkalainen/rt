//
// Created by kafkalainen on 2/3/23.
//

#include <Drawer.hpp>
#include <stdexcept>

namespace Raytracer
{
    Drawer::Drawer(uint8_t *buffer, unsigned int width, unsigned int height)
    {
        m_buffer = buffer;
        m_height = height;
        m_width = width;
    }

    void Drawer::setPixel(unsigned int x, unsigned int y, Color color)
    {
		if (y > m_height)
		{
			throw std::out_of_range("y");
		}

		if (x > m_width)
		{
			throw std::out_of_range("x");
		}

        *(m_buffer + (m_width * y + x) * 4) = color.R;
        *(m_buffer + (m_width * y + x) * 4 + 1) = color.G;
        *(m_buffer + (m_width * y + x) * 4 + 2) = color.B;
        *(m_buffer + (m_width * y + x) * 4 + 3) = color.A;
    }
}

