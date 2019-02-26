#pragma once
#include "Gui.h"
#include <functional>
#include <string>

namespace Illusion
{
	namespace gui
	{

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

			default:
				return sf::Vector2f(10, 10);
			}
		}

		class Button : public Gui
		{

		public:
			Button(sf::Vector2f position, Size size, 
				sf::Color idle=sf::Color::Transparent, 
				sf::Color hover=sf::Color::Transparent, sf::Color pressed=sf::Color::Transparent);
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
			void setStr(const std::string str);
			void setFunction(std::function<void(void)> func); //pass in pointer to func that returns void and takes no parameters

		public:
			sf::Vector2f getPosition()const;
			std::string getString()const { return text_.getString(); }

		private:
			void updateText();

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