//
// Created by kafkalainen on 2/28/23.
//

#ifndef RAYTRACER_HITRECORD_H
#define RAYTRACER_HITRECORD_H

#include "Vec3.h"


namespace Raytracer
{
	class Material;

	struct HitRecord
	{
		point3 p;
		Vec3 normal;
		std::shared_ptr<Material> matPtr{};
		double t;
		bool frontFace;

		HitRecord() : t(0), frontFace(false), normal(0, 0, 0), p(0, 0, 0) {}

		inline void setFaceNormal(const Ray& r, const Vec3& outwardNormal)
		{
			frontFace = dot(r.direction(), outwardNormal) < 0;
			normal = frontFace ? outwardNormal : -outwardNormal;
		}
	};
}

#endif //RAYTRACER_HITRECORD_H
