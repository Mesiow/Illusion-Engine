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
		float time = 0.0f;
	};

	class Animator
	{
	public:
		Animator() = default;

		void addAnimation(Animation &a) 
		{
			animations_.emplace_back(a);
		}

		void update(const float &dt)
		{
			for (std::size_t i = 0; i < animations_.size(); ++i)
			{
				animations_[i].update(dt);
			}
		}

		void apply(int index, sf::Sprite &sprite)
		{
			animations_[index].applyToSprite(sprite);
		}

	private:
		std::vector<Animation> animations_;
	};
}