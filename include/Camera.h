//
// Created by kafkalainen on 2/17/23.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <Ray.h>
#include <Vec3.h>
#include <iostream>

namespace Raytracer
{
	class Camera
	{
		public:
			void initialize(double viewportHeight, double aspectRatio, double focalLength);

			void setOrigin(point3 origin);

			void setHorizontal(Vec3 horizontal);

			void setVertical(Vec3 vertical);

			void setLowerLeftCorner(Vec3 lowerLeftCorner);

			point3 getOrigin();

			Vec3 getHorizontal();

			Vec3 getVertical();

			Vec3 getLowerLeftCorner();

			Ray getRay(double u, double v);

		private:
			double m_viewportHeight{};
			double m_viewportWidth{};
			double m_focalLength{};

			point3 m_origin;
			Vec3 m_horizontal;
			Vec3 m_vertical;
			Vec3 m_lowerLeftCorner;
	};
}
#endif //RAYTRACER_CAMERA_H
