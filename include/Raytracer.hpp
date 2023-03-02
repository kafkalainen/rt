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

			Application();
			void run();

		private:
			sf::RenderWindow    				m_applicationWindow;
			std::unique_ptr<sf::Texture>		m_pixelBufferTexture;
			std::unique_ptr<sf::Sprite>			m_drawable;
			std::unique_ptr<Drawer>             m_drawer;
			uint8_t            					*m_pixelBuffer;
			Camera								m_camera;
			HittableList						m_world;
			int 								m_samplesPerPixel;
			int 								m_maxDepth;

			void initSfml();
			void initBuffers();
			void initRaytracer();
			void initWorld();
			color castRay(const Ray &r, const Hittable &world, int depth);
			void updateBuffer();
			void drawWorld();
			void mainLoop();
			void cleanup();
//			void writeColor(std::ostream &out, color pixel_color, int samples_per_pixel);
    };
}
#endif