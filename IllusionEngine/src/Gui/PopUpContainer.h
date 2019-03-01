#pragma once
#include "Gui.h"

namespace Illusion
{
	namespace gui
	{
		class PopUpContainer : public Gui
		{
		public:
			PopUpContainer(sf::Vector2f position, sf::Vector2f size, 
				sf::Color color, sf::Color outlineColor);
			~PopUpContainer();

			void update(float &dt)override;
			void handleEvents(sf::Event &e)override;
			void draw(sf::RenderTarget &target)override;

		public:
			void showContainer();

		private:
			sf::RectangleShape container_;
			sf::RectangleShape hiddenContainerRect_;

			sf::Color outlineColor;
			sf::Color color;

			sf::Vector2f showPosition_;
			sf::Vector2f hiddenPosition_;

			bool hidden = true;

		};
	}
}