//
// Created by kafkalainen on 2/28/23.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "Ray.h"
#include "HitRecord.h"

namespace Raytracer
{
	class Material
	{
		public:
			virtual bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const = 0;
	};
}

#endif //RAYTRACER_MATERIAL_H
