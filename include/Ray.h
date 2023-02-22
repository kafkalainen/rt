//
// Created by kafkalainen on 2/17/23.
//

#ifndef RAY_H
#define RAY_H

#include <Vec3.h>

namespace Raytracer
{
	class Ray
	{
		public:
			Ray() = default;
			Ray(const point3& origin, const Vec3& direction) : orig(origin), dir(direction) {}

			[[nodiscard]] point3 origin() const  { return orig; }
			[[nodiscard]] Vec3 direction() const { return dir; }

			[[nodiscard]] point3 at(double t) const
			{
				return orig + t * dir;
			}

		public:
			point3 orig;
			Vec3 dir;
	};
}

#endif
