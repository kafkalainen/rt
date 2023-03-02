//
// Created by kafkalainen on 2/28/23.
//

#include "Metal.h"

namespace Raytracer
{
	Metal::Metal(const color &a, double fuzz) : Albedo(a), Fuzz(fuzz) {}

	bool Metal::scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const
	{
		Vec3 reflected = reflect(unitVector(r_in.direction()), rec.normal);
		scattered = Ray(rec.p, reflected + Fuzz * randomInUnitSphere());
		attenuation = Albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
}