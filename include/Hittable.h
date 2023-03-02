//
// Created by kafkalainen on 2/17/23.
//

#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include <Ray.h>
#include "Material.h"

namespace Raytracer
{

	class Hittable
	{
		public:
			virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord &rec) const = 0;
	};
}

#endif //RAYTRACER_HITTABLE_H
