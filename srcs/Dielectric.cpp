//
// Created by kafkalainen on 3/2/23.
//
#include "Dielectric.h"

namespace Raytracer
{
	Dielectric::Dielectric(double index_of_refraction) : ir(index_of_refraction) {}

	bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const
	{
		attenuation = color(1.0, 1.0, 1.0);
		double refraction_ratio = rec.frontFace ? (1.0/ir) : ir;

		Vec3 unit_direction = unitVector(r_in.direction());
		double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

		bool cannot_refract = refraction_ratio * sin_theta > 1.0;
		Vec3 direction;

		if (cannot_refract || reflectance(cos_theta, refraction_ratio) > randomDouble())
			direction = reflect(unit_direction, rec.normal);
		else
			direction = refract(unit_direction, rec.normal, refraction_ratio);

		scattered = Ray(rec.p, direction);
		return true;
	}


	/*
	 * Schlick's approximation for reflectance.
	 */
	double Dielectric::reflectance(double cosine, double ref_idx)
	{
		auto r0 = (1-ref_idx) / (1+ref_idx);
		r0 = r0*r0;
		return r0 + (1-r0)*pow((1 - cosine),5);

	}

}