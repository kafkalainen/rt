//
// Created by kafkalainen on 2/17/23.
//
#include <Camera.h>

namespace Raytracer
{
	void Camera::initialize(
			point3 lookFrom,
			point3 lookAt,
			Vec3 up,
			double verticalFieldOfView,
			double aspectRatio,
			double aperture,
			double focusDist
			)
	{
		auto theta = degrees_to_radians(verticalFieldOfView);

		auto h = tan(theta/2);
		m_viewportHeight = 2.0 * h;
		m_viewportWidth = aspectRatio * m_viewportHeight;

		m_forward = unitVector(lookFrom - lookAt);
		m_right = unitVector(cross(up, m_forward));
		m_up = cross(m_forward, m_right);

		m_origin = lookFrom;
		m_lookAt = lookAt;
		m_horizontal = focusDist * m_viewportWidth * m_right;
		m_vertical = focusDist * m_viewportHeight * m_up;
		m_lowerLeftCorner = m_origin - m_horizontal / 2 - m_vertical / 2 - focusDist * m_forward;
		m_lensRadius = aperture / 2;
	}

	void Camera::setOrigin(point3 origin)
	{
		m_origin = origin;
		auto w = unitVector(m_origin - m_lookAt);
		m_lowerLeftCorner = m_origin - m_horizontal / 2 - m_vertical / 2 - w;
	}

	void Camera::setHorizontal(Vec3 horizontal)
	{
		m_horizontal = horizontal;
	}

	void Camera::setVertical(Vec3 vertical)
	{
		m_vertical = vertical;
	}

	void Camera::setLowerLeftCorner(Vec3 lowerLeftCorner)
	{
		m_lowerLeftCorner = lowerLeftCorner;
	}

	point3 Camera::getOrigin()
	{
		return m_origin;
	}

	Vec3 Camera::getVertical()
	{
		return m_vertical;
	}

	Vec3 Camera::getHorizontal()
	{
		return m_horizontal;
	}

	Vec3 Camera::getLowerLeftCorner()
	{
		return m_lowerLeftCorner;
	}

	Ray Camera::getRay(double s, double t)
	{
		Vec3 rd = m_lensRadius * randomInUnitDisk();
		Vec3 offset = m_right * rd.x() + m_up * rd.y();

		return {

				m_origin + offset,
				m_lowerLeftCorner + s * m_horizontal + t * m_vertical - m_origin - offset
		};
	}
}
