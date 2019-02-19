#pragma once
#include <SFML/Graphics.hpp>
#include "../ResourceManagement/ResourceManager.h"

namespace Illusion
{
	class FPS : public sf::NonCopyable
	{
	public:
		FPS()
		{
			font_ = &ResourceManager::getFont("rubik");
			text_.setFont(*font_);
			text_.setCharacterSize(15);
			text_.setFillColor(sf::Color::White);
			text_.setPosition(0, 0);
		}

		~FPS(){}

		void update(sf::RenderTarget &target)
		{
			time_ = clock_.getElapsedTime();
			int fps = (int)(1.0f / time_.asSeconds());

			target.setView(target.getDefaultView());
			text_.setString(std::to_string(fps));

			clock_.restart();
		}

		void draw(sf::RenderTarget &target)
		{
			target.draw(text_);
		}

	private:
		sf::Clock clock_;
		sf::Time time_;

		sf::Text text_;
		sf::Font *font_;
	};
}