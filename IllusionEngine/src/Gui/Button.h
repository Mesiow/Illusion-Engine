#pragma once
#include "Gui.h"
#include <functional>

namespace Illusion
{
	namespace gui
	{
		enum Colors { idleColor = 0, hoverColor = 1, pressColor = 2 };
		enum Flag { idle = 0, hover = 1, pressed = 2 };
		enum Size { large = 0, medium = 1, small = 2 };
		
		using uint = unsigned int;

		static sf::Vector2f getButtonSize(Size size)
		{
			switch (size)
			{
			case Size::large:
				return sf::Vector2f(256, 80);

			case Size::medium:
				return sf::Vector2f(156, 80);

			case Size::small:
				return sf::Vector2f(156, 40);
			}
		}

		class Button : public Gui
		{

		public:
			Button(sf::Vector2f position, Size size, 
				sf::Color idle, sf::Color hover, sf::Color pressed);
			~Button();

			Button(const Button &other)=default; //copy construct
			Button(Button &&other)=default;//move construct
			Button &operator=(const Button &other)=default; //assignment op

			void handleEvents(sf::Event &e)override;
			void update();
			void draw(sf::RenderTarget &target);

		public:
			void setPosition(const sf::Vector2f pos);
			void setText(const std::string &str, sf::Font &font, uint charSize,
				sf::Color idle, sf::Color hover, sf::Color pressed);
			void setString(const std::string &str);
			void setFunction(std::function<void(void)> func); //pass in pointer to func that returns void and takes no param

		public:
			sf::Vector2f getSize()const;

		private:
			void updateText();
			bool containsMouse()const;

		private:
			std::function<void(void)> function_;

			Flag flag_;
			Size size_;
			sf::Color btnColors_[3];
			sf::Color txtColors_[3];
			sf::Text text_;
			sf::RectangleShape button_;

			sf::Vector2f position_;
		};
	}
}