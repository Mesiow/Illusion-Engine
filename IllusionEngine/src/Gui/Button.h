#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
namespace Illusion
{
	namespace gui
	{
		enum Colors { idleColor = 0, hoverColor = 1, pressColor = 2 };
		enum Flag { idle = 0, hover = 1, pressed = 2 };
		enum Size { large = 0, medium = 1, small = 2 };
		
		using uint = unsigned int;

		class Button
		{

		public:
			Button(sf::Vector2f position, Size size, 
				sf::Color idle, sf::Color hover, sf::Color pressed);
			~Button();

			void handleEvents(sf::Event &e);
			void update();
			void draw(sf::RenderTarget &target);

		public:
			void setPosition(const sf::Vector2f pos);
			void setText(const std::string &str, sf::Font &font,
				sf::Color idle, sf::Color hover, sf::Color pressed);
			void setFunction(std::function<void(void)> func); //pass in pointer to func that returns void and takes no param

		private:
			bool contains();

		private:
			std::function<void(void)> function_;

			Flag flag;
			sf::Color btnColors_[3];
			sf::Color txtColors_[3];
			sf::Font *font_;
			sf::Text text_;
			sf::RectangleShape button_;

		private:
			sf::Vector2f position_;
			sf::Vector2f size_;
		};
	}
}