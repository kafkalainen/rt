//
// Created by kafkalainen on 2/17/23.
//

#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include <Ray.h>

namespace Raytracer
{
	struct HitRecord
	{
		point3 p;
		Vec3 normal;
		double t;
		bool frontFace;

		HitRecord() : t(0), frontFace(false), normal(0, 0, 0), p(0, 0, 0) {}

		inline void setFaceNormal(const Ray& r, const Vec3& outwardNormal)
		{
			frontFace = dot(r.direction(), outwardNormal) < 0;
			normal = frontFace ? outwardNormal : -outwardNormal;
		}
	};

	class Hittable
	{
		public:
			virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord &rec) const = 0;
	};
}

#endif //RAYTRACER_HITTABLE_H
