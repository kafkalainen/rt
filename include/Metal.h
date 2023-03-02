//
// Created by kafkalainen on 2/28/23.
//

#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H

#include "Material.h"

namespace Raytracer
{
	class Metal : public Material
	{
		public:
			color Albedo;
			double Fuzz;

			Metal(const color& a, double fuzz);

			bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override;
	};
}


#endif //RAYTRACER_METAL_H
