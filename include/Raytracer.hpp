#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Camera.h>
#include <Drawer.hpp>
#include "Hittable.h"
#include "HittableList.h"

namespace Raytracer
{
    using namespace sf;

    class Application
	{
		public:
			const unsigned int Width = 640;
			const unsigned int Height = 480;
			const sf::Vector2u WindowRect = Vector2u(Width, Height);

			void run();

		private:
			sf::RenderWindow    m_applicationWindow;
			sf::Texture         m_readOnlyTexture;
			sf::Sprite          m_drawable;
			uint8_t             *m_pixelBuffer;
			Drawer              *m_drawer;
			Camera				m_camera;
			HittableList		m_world;
			int 				m_samplesPerPixel;

			void initSfml();
			void initBuffers();
			void initRaytracer();
			void initWorld();
			static color castRay(const Ray &r, const Hittable &world);
			void updateBuffer();
			void drawWorld();
			void mainLoop();
			void cleanup();
    };
}
#endif