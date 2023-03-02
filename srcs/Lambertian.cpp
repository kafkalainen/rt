//
// Created by kafkalainen on 2/28/23.
//

#include "Lambertian.h"

namespace Raytracer
{

	bool Lambertian::scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const
	{
		auto scatterDirection = rec.normal + randomUnitVector();

		if (scatterDirection.nearZero())
		{
			scatterDirection = rec.normal;
		}

		scattered = Ray(rec.p, scatterDirection);
		attenuation = albedo;
		return true;
	}
}
