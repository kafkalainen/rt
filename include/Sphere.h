
//
// Created by kafkalainen on 2/17/23.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H
#include <utility>
#include "Material.h"

namespace Raytracer
{
	class Sphere : public Hittable
	{
		public:
			point3 Center;
			double Radius;
			std::shared_ptr<Material> matPtr;

			Sphere(point3 cen, double r, std::shared_ptr<Material> m) : Center(cen), Radius(r), matPtr(std::move(m)) {};

			bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
	};
}
#endif //RAYTRACER_SPHERE_H
