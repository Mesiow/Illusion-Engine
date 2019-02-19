#include "AnimationComponent.h"

namespace Illusion
{
	AnimationComponent::AnimationComponent(sf::Sprite &sprite, sf::Texture &textureSheet)
		:sprite_(sprite), textureSheet_(textureSheet), lastAnimation_(nullptr)
	{
		
	}

	AnimationComponent::~AnimationComponent()
	{
		for (auto &v : animations_)
			delete v.second;
	}

	bool AnimationComponent::play(const std::string key, const float &dt, const bool priority)
	{
		if (priorityAnimation_) //if a priority animation exists
		{
			if (priorityAnimation_ == animations_[key]) //if priority animation is the current one at the key pos
			{
				if (lastAnimation_ != animations_[key])
				{
					if (lastAnimation_ == nullptr)
						lastAnimation_ = animations_[key];
					else
					{
						lastAnimation_->reset();
						lastAnimation_ = animations_[key];
					}
				}

				if (animations_[key]->play(dt))
					priorityAnimation_ = nullptr;
			}
		}
		else //play animation if no other priority animation exists
		{
			if (priority) //if this is a priority animation, initialize it
			{
				priorityAnimation_ = animations_[key];
			}

			if (lastAnimation_ != animations_[key])
			{
				if (lastAnimation_ == nullptr)
					lastAnimation_ = animations_[key];
				else
				{
					lastAnimation_->reset();
					lastAnimation_ = animations_[key];
				}
			}
			animations_[key]->play(dt);
		}

		return animations_[key]->isDone();
	}

	void AnimationComponent::addAnimation(const std::string key, float animTimer, 
		int startFrameX, int startFrameY, 
		int framesX, int framesY,
		int width, int height)
	{
		animations_[key] = new Animation(this->sprite_, this->textureSheet_, animTimer,
			startFrameX, startFrameY, framesX, framesY, width, height);
	}

	void AnimationComponent::startAnimation(const std::string anim)
	{

	}
	const bool AnimationComponent::isDone(const std::string key)
	{
		return animations_[key]->isDone();
	}
}