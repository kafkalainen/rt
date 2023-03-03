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
			void initialize(
					point3 lookFrom,
					point3 lookAt,
					Vec3 up,
					double verticalFieldOfView,
					double aspectRatio,
					double aperture,
					double focusDist
					);

			void setOrigin(point3 origin);

			void setHorizontal(Vec3 horizontal);

			void setVertical(Vec3 vertical);

			void setLowerLeftCorner(Vec3 lowerLeftCorner);

			point3 getOrigin();

			Vec3 getHorizontal();

			Vec3 getVertical();

			Vec3 getLowerLeftCorner();

			Ray getRay(double s, double t);

		private:
			double m_viewportHeight{};
			double m_viewportWidth{};

			point3 m_origin;
			point3 m_lookAt;
			Vec3 m_horizontal;
			Vec3 m_vertical;
			Vec3 m_lowerLeftCorner;
			Vec3 m_forward;
			Vec3 m_right;
			Vec3 m_up;
			double m_lensRadius;
	};
}
#endif //RAYTRACER_CAMERA_H
