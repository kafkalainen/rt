//
// Created by kafkalainen on 2/3/23.
//

#include <Color.hpp>
#include <Vec3.h>
#include "Constants.h"

namespace Raytracer
{
    Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        R = r;
        G = g;
        B = b;
        A = a;
    }

	Color::Color(double r, double g, double b, double a)
	{
		R = static_cast<int>(256 * clamp(r, 0.0, 0.999));
		G = static_cast<int>(256 * clamp(g, 0.0, 0.999));
		B = static_cast<int>(256 * clamp(b, 0.0, 0.999));
		A = static_cast<int>(256 * clamp(a, 0.0, 0.999));
	}

	Color::Color(double r, double g, double b, double a, int samples)
	{
		auto scale = 1.0 / samples;

		r = sqrt(r * scale);
		g = sqrt(g * scale);
		b = sqrt(b * scale);
		a = sqrt(a * scale);

		R = static_cast<int>(256 * clamp(r, 0.0, 0.999));
		G = static_cast<int>(256 * clamp(g, 0.0, 0.999));
		B = static_cast<int>(256 * clamp(b, 0.0, 0.999));
		A = static_cast<int>(256 * clamp(a, 0.0, 0.999));
	}
}
