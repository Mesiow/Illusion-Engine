#include "Button.h"
#include "../Game.h"
namespace Illusion
{
	namespace gui
	{
		Button::Button(sf::Vector2f position, Size size, 
			sf::Color idle, sf::Color hover, sf::Color pressed)
		{
			flag_ = Flag::idle;
			btnColors_[Colors::idleColor] = idle;
			btnColors_[Colors::hoverColor] = hover;
			btnColors_[Colors::pressColor] = pressed;

			this->position_ = position;
			this->size_ = size;

			switch (size)
			{
			case Size::large:
				button_.setSize(getButtonSize(size));
				break;

			case Size::medium:
				button_.setSize(getButtonSize(size));

			case Size::small:
				button_.setSize(getButtonSize(size));
				break;
			}

			//set position of button in middle of window without setting the buttons origin
			button_.setPosition(sf::Vector2f(position.x - button_.getGlobalBounds().width/2, 
				position.y + button_.getGlobalBounds().height/2));

			button_.setFillColor(btnColors_[Colors::idleColor]);
		}

		Button::~Button()
		{

		}

		void Button::handleEvents(sf::Event &e)
		{
			flag_ = Flag::idle;
			if (containsMouse())
				flag_ = Flag::hover;

			switch (e.type)
			{
			case sf::Event::MouseButtonPressed:
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					if (containsMouse())
					{
						flag_ = Flag::pressed;
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
			switch (flag_)
			{
			case Flag::idle:
				button_.setFillColor(btnColors_[Colors::idleColor]);
				text_.setFillColor(txtColors_[Colors::idleColor]);
				break;
			case Flag::hover:
				button_.setFillColor(btnColors_[Colors::hoverColor]);
				text_.setFillColor(txtColors_[Colors::hoverColor]);
				break;
			case Flag::pressed:
				button_.setFillColor(btnColors_[Colors::pressColor]);
				text_.setFillColor(txtColors_[Colors::pressColor]);
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
			updateText();
		}

		void Button::setText(const std::string &str, sf::Font &font, uint charSize,
			sf::Color idle, sf::Color hover, sf::Color pressed)
		{
			txtColors_[Colors::idleColor] = idle;
			txtColors_[Colors::hoverColor] = hover;
			txtColors_[Colors::pressColor] = pressed;

			text_.setCharacterSize(charSize);
			text_.setFont(font);
			text_.setString(str);

			/*text_.setOrigin(text_.getGlobalBounds().left + text_.getGlobalBounds().width / 2,
				text_.getGlobalBounds().top - text_.getGlobalBounds().height / 2);
*/
			text_.setPosition(
				button_.getPosition().x + (button_.getGlobalBounds().width / 2.f) - text_.getGlobalBounds().width / 2.f,
				button_.getPosition().y + (button_.getGlobalBounds().height / 3.f) - text_.getGlobalBounds().height / 2.f
			);

			text_.setFillColor(txtColors_[Colors::idleColor]);
		}

		void Button::setStr(const std::string str)
		{
			text_.setString(str);
			updateText();
		}

		void Button::updateText()
		{
			text_.setPosition(
				button_.getPosition().x + (button_.getGlobalBounds().width / 2.f) - text_.getGlobalBounds().width / 2.f,
				button_.getPosition().y + (button_.getGlobalBounds().height / 3.f) - text_.getGlobalBounds().height / 2.f
			);
			/*text_.setPosition(button_.getPosition().x + text_.getGlobalBounds().width/10,
	  		button_.getPosition().y + text_.getGlobalBounds().height);*/
		}

		void Button::setFunction(std::function<void(void)> func)
		{
			function_ = func;
		}

		sf::Vector2f Button::getPosition() const
		{
			return sf::Vector2f(position_.x - button_.getGlobalBounds().width / 2,
				position_.y + button_.getGlobalBounds().height / 2); //get position of origin
		}

		bool Button::containsMouse()const
		{
			auto mousePos = sf::Mouse::getPosition(Game::getWindow());
			if (button_.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
				return true;

			return false;
		}
    }
}