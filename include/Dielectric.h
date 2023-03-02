//
// Created by kafkalainen on 3/2/23.
//

#ifndef RAYTRACER_DIELECTRIC_H
#define RAYTRACER_DIELECTRIC_H
#include "Ray.h"
#include "HitRecord.h"
#include "Vec3.h"
#include "Material.h"

namespace Raytracer
{
	class Dielectric : public Material
	{
		public:
			double ir; // Index of Refraction

			explicit Dielectric(double index_of_refraction);

			bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override;

		private:
			static double reflectance(double cosine, double ref_idx);
	};
}
#endif //RAYTRACER_DIELECTRIC_H
