#pragma once
#include "Gui.h"

namespace Illusion
{
	namespace gui
	{
		class Slider : public Gui
		{
		public:
			Slider(sf::Vector2f position);
			~Slider();

		public:
			void handleEvents(sf::Event &e)override;
			void update(float &dt)override;
			void draw(sf::RenderTarget &target)override;

		private:
			void moveSlider();
			void initialize();

			bool onLine();

		private:
			sf::RectangleShape slider_;
			sf::Vertex line_[2];

			sf::Vector2f position_;
		};
	}
}