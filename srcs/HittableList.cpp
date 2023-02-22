//
// Created by kafkalainen on 2/19/23.
//
#include <HittableList.h>

namespace Raytracer
{
	bool HittableList::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
	{
		HitRecord temp_rec;
		bool hitAnything = false;
		auto closestObject = t_max;

		for (const auto& object : objects) {
			if (object->hit(r, t_min, closestObject, temp_rec)) {
				hitAnything = true;
				closestObject = temp_rec.t;
				rec = temp_rec;
			}
		}

		return hitAnything;
	}
}
