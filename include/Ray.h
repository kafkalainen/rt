//
// Created by kafkalainen on 2/17/23.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <Vec3.h>

namespace Raytracer
{
	class Ray
	{
		public:
			point3 orig;
			Vec3 dir;

			Ray() = default;
			Ray(const point3& origin, const Vec3& direction) : orig(origin), dir(direction) {}

			[[nodiscard]] point3 origin() const  { return orig; }
			[[nodiscard]] Vec3 direction() const { return dir; }

			[[nodiscard]] point3 at(double t) const
			{
				return orig + t * dir;
			}

	};
}

#endif //RAYTRACER_RAY_H
