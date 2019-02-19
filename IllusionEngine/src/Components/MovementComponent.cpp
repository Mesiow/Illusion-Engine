#include "MovementComponent.h"

namespace Illusion
{
	MovementComponent::MovementComponent(sf::Sprite &sprite, float maxVelocity,
		float acceleration, float deceleration)
		:sprite_(sprite), maxVelocity_(maxVelocity), acceleration_(acceleration),
		deceleration_(deceleration)
	{
	
	}

	MovementComponent::~MovementComponent()
	{

	}

	void MovementComponent::move(const float xdir, const float ydir, const float & dt)
	{
		velocity_.x += acceleration_ * xdir;
		velocity_.y += acceleration_ * ydir;
	}
	void MovementComponent::update(const float &dt)
	{
		/////////////////////
		// X Velocity update
		if (this->velocity_.x < 0) //if we are moving left
		{
			if (velocity_.x < -maxVelocity_) //if we are less than the negative maxVelocity make sure we can't go faster
				velocity_.x = -maxVelocity_;

			velocity_.x += deceleration_;
			if (velocity_.x > 0)
				velocity_.x = 0;
		}
		else if (this->velocity_.x > 0)
		{
			if (velocity_.x > maxVelocity_)
				velocity_.x = maxVelocity_;

			velocity_.x -= deceleration_;
			if (velocity_.x < 0)
				velocity_.x = 0;
		}
		////////////////////

		// Y Velocity update
		if (this->velocity_.y < 0)
		{
			if (velocity_.y < -maxVelocity_)
				velocity_.y = -maxVelocity_;

			velocity_.y += deceleration_;
			if (velocity_.y > 0)
				velocity_.y = 0;
		}
		else if (this->velocity_.y > 0)
		{
			if (velocity_.y > maxVelocity_)
				velocity_.y = maxVelocity_;

			velocity_.y -= deceleration_;
			if (velocity_.y < 0)
				velocity_.y = 0;
		}

		sprite_.move(velocity_ * dt);
	}
}