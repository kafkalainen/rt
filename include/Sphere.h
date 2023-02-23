//
// Created by kafkalainen on 2/17/23.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

namespace Raytracer
{
	class Sphere : public Hittable
	{
		public:
			point3 Center;
			double Radius;

			Sphere(point3 center, double r) : Center (center), Radius(r) {};

			bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
	};
}
#endif //RAYTRACER_SPHERE_H
