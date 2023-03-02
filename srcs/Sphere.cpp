//
// Created by kafkalainen on 2/17/23.
//
#include "Hittable.h"
#include "Ray.h"
#include "Sphere.h"
#include "Material.h"
#include "Vec3.h"

namespace Raytracer
{
	bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
	{
		Vec3 oc = r.origin() - Center;
		auto a = r.direction().lengthSquared();
		auto half_b = dot(oc, r.direction());
		auto c = oc.lengthSquared() - Radius * Radius;

		auto discriminant = half_b*half_b - a*c;
		if (discriminant < 0) return false;
		auto sqrtd = sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range.
		auto root = (-half_b - sqrtd) / a;
		if (root < t_min || t_max < root)
		{
			root = (-half_b + sqrtd) / a;
			if (root < t_min || t_max < root)
				return false;
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		Vec3 outwardNormal = (rec.p - Center) / Radius;
		rec.setFaceNormal(r, outwardNormal);
		rec.matPtr = matPtr;

		return true;
	}
}