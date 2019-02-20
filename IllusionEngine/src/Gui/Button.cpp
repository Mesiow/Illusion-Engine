#include "Button.h"
#include "../Game.h"
namespace Illusion
{
	namespace gui
	{
		Button::Button(sf::Vector2f position, Size size, 
			sf::Color idle, sf::Color hover, sf::Color pressed)
		{
			btnColors_[Colors::idleColor] = idle;
			btnColors_[Colors::hoverColor] = hover;
			btnColors_[Colors::pressColor] = pressed;

			this->position_ = position;

			switch (size)
			{
			case Size::large:
				button_.setSize({ 256, 80 });
				break;

			case Size::medium:
				button_.setSize({ 156, 80 });

			case Size::small:
				button_.setSize({ 156, 40 });
				break;
			}

			button_.setOrigin(button_.getGlobalBounds().left + button_.getGlobalBounds().width / 2,
				button_.getGlobalBounds().top - button_.getGlobalBounds().height / 2);

			button_.setPosition(position);
			button_.setFillColor(btnColors_[Colors::idleColor]);
		}

		Button::~Button()
		{
		
		}

		void Button::handleEvents(sf::Event &e)
		{
			flag = Flag::idle;
			if (contains())
				flag = Flag::hover;

			switch (e.type)
			{
			case sf::Event::MouseButtonPressed:
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					if (contains())
					{
						flag = Flag::pressed;
						function_();
					}

				}
			}
			break;

			default:
				break;
			} 

		}

		void Button::update()
		{
			switch (flag)
			{
			case Flag::idle:
				button_.setFillColor(btnColors_[Colors::idleColor]);
				break;
			case Flag::hover:
				button_.setFillColor(btnColors_[Colors::hoverColor]);
				break;
			case Flag::pressed:
				button_.setFillColor(btnColors_[Colors::pressColor]);
				break;

			default:
				break;
			}
		}

		void Button::draw(sf::RenderTarget &target)
		{
			target.draw(button_);
			target.draw(text_);
		}

		void Button::setPosition(const sf::Vector2f pos)
		{
			button_.setPosition(pos);
		}

		void Button::setText(const std::string &str, sf::Font &font,
			sf::Color idle, sf::Color hover, sf::Color pressed)
		{
			txtColors_[Colors::idleColor] = idle;
			txtColors_[Colors::hoverColor] = hover;
			txtColors_[Colors::pressColor] = pressed;

			text_.setFont(font);
			text_.setString(str);
			text_.setFillColor(txtColors_[Colors::idleColor]);
		}

		void Button::setFunction(std::function<void(void)> func)
		{
			function_ = func;
		}

		bool Button::contains()
		{
			auto mousePos = sf::Mouse::getPosition(Game::getWindow());
			if (button_.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
				return true;

			return false;
		}
	}
}