//
// Created by joonasvalamaki on 2/3/23.
//
#ifndef DRAWER_HPP
#define DRAWER_HPP
#include <cstdint>
#include "Color.hpp"

namespace Raytracer
{
    class Drawer
    {
        public:
			Drawer();

            void	setPixel(unsigned int x, unsigned int y, Color color);
			void	initialize(uint8_t *buffer, unsigned int width, unsigned int height);

        private:
            uint8_t			*m_buffer;
            unsigned int	m_width;
            unsigned int	m_height;
    };
}

#endif //DRAWER_HPP
