//
// Created by joonasvalamaki on 2/3/23.
//

#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>
#include <Vec3.h>

namespace Raytracer
{
    class Color
    {
        public:
            Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
			Color(double r, double g, double b, double a);
			Color(double r, double g, double b, double a, int samples);
			explicit Color(color a) : Color(a.x(), a.y(), a.z(), 1.0) { }
			Color(color a, int samples) : Color(a.x(), a.y(), a.z(), samples, samples) { }

            uint8_t R;
            uint8_t G;
            uint8_t B;
            uint8_t A;
    };
}

#endif //COLOR_HPP
