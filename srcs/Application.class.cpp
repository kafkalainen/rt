#include <cstring>
#include <Color.hpp>
#include <Raytracer.hpp>
#include "Hittable.h"
#include "Constants.h"
#include "Sphere.h"

namespace Raytracer
{
    void Application::run()
	{
        Application::initSfml();
        Application::initBuffers();
		Application::initRaytracer();
		Application::initWorld();
        Application::mainLoop();
        Application::cleanup();
    }

    void Application::initSfml()
    {
        Vector2u windowSize = Vector2u(Width, Height);
        m_applicationWindow.create( sf::VideoMode(windowSize), "rt");
        std::cout << "Initialized" << std::endl;
    }

    void Application::initBuffers()
    {
        if (!m_readOnlyTexture.create(WindowRect))
        {
            throw std::exception();
        }

        m_pixelBuffer = (uint8_t*)malloc((sizeof(uint8_t) * Width * Height * 4) + 1);
        if (m_pixelBuffer == nullptr)
        {
            throw std::exception();
        }

        m_drawer = new Drawer(m_pixelBuffer, Width, Height);
        m_drawable.setTexture(m_readOnlyTexture);
    }

	void Application::initWorld()
	{
		m_world.add(make_shared<Sphere>(point3(0,0,-1), 0.5));
		m_world.add(make_shared<Sphere>(point3(0,-100.5,-1), 100));
	}

    void Application::mainLoop()
    {
        std::cout << "Loop" << std::endl;
		updateBuffer();
        while (m_applicationWindow.isOpen())
        {
            sf::Event event {};
            while (m_applicationWindow.pollEvent(event))
            {
				switch (event.type)
				{
					case sf::Event::Closed:
						m_applicationWindow.close();
					case sf::Event::KeyPressed:
						if (event.key.code == sf::Keyboard::W)
						{
							auto origin = m_camera.getOrigin();
							origin[1] += 0.1;
							m_camera.setOrigin(origin);
						}
						if (event.key.code == sf::Keyboard::S)
						{
							auto origin = m_camera.getOrigin();
							origin[1] -= 0.1;
							m_camera.setOrigin(origin);
						}
						if (event.key.code == sf::Keyboard::Z)
						{
							auto origin = m_camera.getOrigin();
							origin[2] += 0.1;
							m_camera.setOrigin(origin);
						}
						if (event.key.code == sf::Keyboard::X)
						{
							auto origin = m_camera.getOrigin();
							origin[2] -= 0.1;
							m_camera.setOrigin(origin);
						}
						updateBuffer();
				}
            }

			m_readOnlyTexture.update(m_pixelBuffer);

            m_applicationWindow.clear();
            m_applicationWindow.draw(m_drawable);
            m_applicationWindow.display();
        }
    }

    void Application::cleanup()
    {
        free(m_pixelBuffer);
        std::cout << "Cleanup" << std::endl;
    }

	void Application::updateBuffer()
	{
		bzero(m_pixelBuffer, (sizeof(uint8_t) * Width * Height * 4));
		Application::drawWorld();
		m_readOnlyTexture.update(m_pixelBuffer);
	}

	void Application::drawWorld()
	{
		for (int j = (int)Height - 1; j >= 0; --j)
		{
			for (int i = 0; i < Width; ++i)
			{
				color pixelColor(0, 0, 0);
				for (int s = 0; s < m_samplesPerPixel; ++s)
				{
					auto u = (i + random_double()) / (Width - 1);
					auto v = (j + random_double()) / (Height - 1);
					Ray r = m_camera.getRay(u, v);
					pixelColor += castRay(r, m_world);
				}
				m_drawer->setPixel(i, j, Color(pixelColor, m_samplesPerPixel));
			}
		}
	}

	void Application::initRaytracer()
	{
		m_camera.initialize(2.0, 4.0 / 3.0, 1.0);
		m_samplesPerPixel = 3;
	}

	color Application::castRay(const Ray &r, const Hittable &world)
	{
		HitRecord rec;
		if (world.hit(r, 0, infinity, rec)) {
			return 0.5 * (rec.normal + color(1,1,1));
		}
		Vec3 unit_direction = unit_vector(r.direction());
		auto t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
	}
};