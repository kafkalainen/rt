#include <cstring>
#include <Color.hpp>
#include <Raytracer.hpp>
#include "Hittable.h"
#include "Constants.h"
#include "Sphere.h"
#include "Vec3.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

namespace Raytracer
{
	Application::Application() :
		m_pixelBufferTexture(std::make_unique<Texture>()),
		m_drawable(std::make_unique<Sprite>()),
		m_pixelBuffer(nullptr),
		m_drawer(std::make_unique<Drawer>()),
		m_samplesPerPixel(50),
		m_maxDepth(50) {}

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
        m_applicationWindow.create( sf::VideoMode(WindowRect), "rt");
        std::cout << "Initialized" << std::endl;
    }

    void Application::initBuffers()
    {
        if (!m_pixelBufferTexture->create(WindowRect))
        {
            throw std::exception();
        }

        m_pixelBuffer = (uint8_t*)malloc((sizeof(uint8_t) * Width * Height * 4) + 1);
        if (m_pixelBuffer == nullptr)
        {
            throw std::exception();
        }

        m_drawer->initialize(m_pixelBuffer, Width, Height);
        m_drawable->setTexture(*m_pixelBufferTexture);
		std::cout << "Initialized buffers" << std::endl;
    }

	void Application::initWorld()
	{
		auto material_ground = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
		auto material_center = make_shared<Dielectric>(1.5);
		auto material_left   = make_shared<Metal>(color(0.8, 0.8, 0.8), 0.3);
		auto material_right  = make_shared<Metal>(color(0.8, 0.6, 0.2), 1.0);

		m_world.add(make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
		m_world.add(make_shared<Sphere>(point3( 0.0,    0.0, -1.0),   -0.5, material_center));
		m_world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
		m_world.add(make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
		std::cout << "Initialized world" << std::endl;
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
					{
						m_applicationWindow.close();
						break;
					}
					case sf::Event::KeyPressed:
					{

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
						if (event.key.code == sf::Keyboard::A)
						{
							auto origin = m_camera.getOrigin();
							origin[0] += 0.1;
							m_camera.setOrigin(origin);
						}
						if (event.key.code == sf::Keyboard::D)
						{
							auto origin = m_camera.getOrigin();
							origin[0] -= 0.1;
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
						break;
					}
					case Event::Resized:
					case Event::LostFocus:
					case Event::GainedFocus:
					case Event::TextEntered:
					case Event::KeyReleased:
					case Event::MouseWheelScrolled:
					case Event::MouseButtonPressed:
					case Event::MouseButtonReleased:
					case Event::MouseMoved:
					case Event::MouseEntered:
					case Event::MouseLeft:
					case Event::JoystickButtonPressed:
					case Event::JoystickButtonReleased:
					case Event::JoystickMoved:
					case Event::JoystickConnected:
					case Event::JoystickDisconnected:
					case Event::TouchBegan:
					case Event::TouchMoved:
					case Event::TouchEnded:
					case Event::SensorChanged:
					case Event::Count:
						break;
				}
            }

            m_applicationWindow.clear();
            m_applicationWindow.draw(*m_drawable);
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
		m_pixelBufferTexture->update(m_pixelBuffer);
	}

	void Application::drawWorld()
	{
		for (int j = 0; j < Height; ++j)
		{
			for (int i = 0; i < Width; ++i)
			{
				color pixelColor(0, 0, 0);
				for (int s = 0; s < m_samplesPerPixel; ++s)
				{
					auto u = (i + randomDouble(0, 0)) / (Width - 1);
					auto v = (j + randomDouble(0, 0)) / (Height - 1);
					Ray r = m_camera.getRay(u, v);
					pixelColor += castRay(r, m_world, m_maxDepth);
				}
				m_drawer->setPixel(i, (Height - 1) - j,
								   Color(pixelColor, m_samplesPerPixel));
			}
			std::cout.clear();
			std::cout << (float)j / static_cast<float>(Height) * 100 << "% drawn" << std::endl << std::flush;
		}
	}

	void Application::initRaytracer()
	{
		m_camera.initialize(2.0, 4.0 / 3.0, 1.0);
		m_samplesPerPixel = 50;
		m_maxDepth = 50;
	}

	color Application::castRay(const Ray &r, const Hittable &world, int depth)
	{
		HitRecord rec;
		if (depth <= 0)
		{
			return {0, 0, 0};
		}

		if (world.hit(r, 0.001, infinity, rec))
		{
			Ray scattered;
			color attenuation;
			if (rec.matPtr->scatter(r, rec, attenuation, scattered))
			{
				return attenuation * castRay(scattered, world, depth - 1);
			}
			return {0,0,0};
		}

		Vec3 unit_direction = unitVector(r.direction());
		auto t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
	}
}