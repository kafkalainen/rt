//
// Created by kafkalainen on 2/28/23.
//

#ifndef RAYTRACER_LAMBERTIAN_H
#define RAYTRACER_LAMBERTIAN_H

#include "Material.h"

namespace Raytracer
{

	class Lambertian : public Material
	{
		public:
			explicit Lambertian(const color &a) : albedo(a) {}

			bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const override;

		public:
			color albedo;
	};
}
#endif //RAYTRACER_LAMBERTIAN_H
