//
// Created by kafkalainen on 2/17/23.
//
#include <Camera.h>

namespace Raytracer
{
	void Camera::initialize(double viewportHeight, double aspectRatio, double focalLength)
	{
		m_viewportHeight = viewportHeight;
		m_viewportWidth = aspectRatio * m_viewportHeight;
		m_focalLength = focalLength;

		m_origin = point3(0, 0, 0);
		m_horizontal = Vec3(m_viewportWidth, 0, 0);
		m_vertical = Vec3(0, m_viewportHeight, 0);
		m_lowerLeftCorner = m_origin - m_horizontal / 2 - m_vertical / 2 - Vec3(0, 0, m_focalLength);
	}

	void Camera::setOrigin(point3 origin)
	{
		m_origin = origin;
		m_lowerLeftCorner = m_origin - m_horizontal / 2 - m_vertical / 2 - Vec3(0, 0, m_focalLength);
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

	Ray Camera::getRay(double u, double v)
	{
		return { m_origin, (m_lowerLeftCorner + u * m_horizontal + v * m_vertical - m_origin) };
	}
}
