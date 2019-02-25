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
			void draw(sf::RenderTarget &target)override;

		private:
			void initialize();

		private:
			sf::RectangleShape slider_;
			sf::Vertex line_[2];

			sf::Vector2f position_;
		};
	}
}