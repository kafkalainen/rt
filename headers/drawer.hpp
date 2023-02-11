//
// Created by joonasvalamaki on 2/3/23.
//
#ifndef RT_DRAWER_HPP
#define RT_DRAWER_HPP
#include <stdint.h>
#include "color.hpp"

namespace rt
{
    class Drawer
    {
        public:
            Drawer(uint8_t *buffer, unsigned int width, unsigned int height);
            void setPixel(unsigned int x, unsigned int y, Color color);

        private:
            uint8_t *m_buffer;
            unsigned int m_width;
            unsigned int m_height;
    };
}

#endif //RT_DRAWER_HPP
