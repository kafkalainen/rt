//
// Created by kafkalainen on 2/19/23.
//

#ifndef RAYTRACER_HITTABLELIST_H
#define RAYTRACER_HITTABLELIST_H

#include <Hittable.h>

#include <memory>
#include <utility>
#include <vector>

using std::shared_ptr;
using std::make_shared;

namespace Raytracer
{
	class HittableList : public Hittable
	{
		public:
			std::vector<shared_ptr<Hittable>> objects;

			HittableList() = default;
			explicit HittableList(const shared_ptr<Hittable>& object) { add(object); }

			void add(const shared_ptr<Hittable>& object) { objects.push_back(object); }
			void clear() { objects.clear(); }

			bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
	};
}
#endif //RAYTRACER_HITTABLELIST_H
