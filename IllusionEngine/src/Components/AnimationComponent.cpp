#include "../pcHeaders.h"
#include "AnimationComponent.h"

namespace Illusion
{
	Animation::Animation(sf::Texture &textureSheet, int x, int y, int width, int height, int nmberOfFrames, float holdtime)
		:holdTime_(holdtime)
	{
		frames_.reserve(nmberOfFrames);

		texture_ = &textureSheet;

		for (int i = 0; i < nmberOfFrames; i++)
		{
			frames_.emplace_back(sf::IntRect(x, y, width, height));
			x += width;
		}
	}

	void Animation::update(const float &dt)
	{
		time += dt;
		while (time >= holdTime_)
		{
			time -= holdTime_; //decrease
			advance();
		}
	}

	void Animation::applyToSprite(sf::Sprite &sprite) const
	{
		sprite.setTexture(*texture_);
		sprite.setTextureRect(frames_[indexFrame_]);
	}

	void Animation::advance()
	{
		//increment then check
		if (++indexFrame_ >= int(frames_.size()))
		{
			indexFrame_ = 0;
		}
	}
}