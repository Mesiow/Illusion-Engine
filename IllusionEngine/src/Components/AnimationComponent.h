#pragma once
#include "../ResourceManagement/ResourceManager.h"

namespace Illusion
{
	class Animation
	{
	public:
		Animation() = default;
		Animation(sf::Texture &textureSheet, int x, int y, int width, int height, int nmberOfFrames, float holdtime);

	public:
		void update(const float& dt);
		void applyToSprite(sf::Sprite &sprite)const;

	private:
		void advance();

	private:
		sf::Texture *texture_;
		std::vector<sf::IntRect> frames_;

		float holdTime_;
		int indexFrame_ = 0;
		float time_ = 0.0f;
	};
}