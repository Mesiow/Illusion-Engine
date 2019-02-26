#pragma once
#include "Gui.h"

namespace Illusion
{
	namespace gui
	{
		class Slider : public Gui
		{
		public:
			Slider(sf::Vector2f position, sf::Vector2f size,
				sf::Color idle, sf::Color hover, sf::Color pressed);
			~Slider();

		public:
			void handleEvents(sf::Event &e)override;
			void update();
			void draw(sf::RenderTarget &target)override;

		private:
			void moveSlider();
			void initialize();

			bool onLine();

		private:
			sf::RectangleShape slider_;
			sf::Vertex line_[2];

			sf::Color colors_[3];
			sf::Vector2f position_;

			Flag flag_;
		};
	}
}