#pragma once
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
			++fpsCount_;
			if (delay_.getElapsedTime().asSeconds() > 0.1f)
			{
				fps_ = (int)(fpsCount_ / clock_.restart().asSeconds());
				fpsCount_ = 0;
				delay_.restart();
			}

			target.setView(target.getDefaultView());
			text_.setString(std::to_string(fps_));
		}

		void draw(sf::RenderTarget &target)
		{
			target.draw(text_);
		}

	private:
		sf::Clock delay_;
		sf::Clock clock_;
		sf::Time time_;

		int fps_;
		int fpsCount_ = 0;

		sf::Text text_;
		sf::Font *font_;
	};
}