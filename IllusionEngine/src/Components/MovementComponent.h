#pragma once
#include <SFML/Graphics.hpp>

namespace Illusion
{
	class MovementComponent
	{
	public:
		MovementComponent(sf::Sprite &sprite, float maxVelocity, 
			float acceleration, float deceleration);
		~MovementComponent();

		void move(const float xdir, const float ydir, const float &dt);
		void update(const float &dt);


	public:
		sf::Vector2f &getVelocity() { return velocity_; }
		const bool isIdle()const { return velocity_.x==0.0f && velocity_.y==0 ; }
		const float getMaxVelocity()const { return maxVelocity_; }

	private:
		sf::Vector2f velocity_;
		float maxVelocity_;
		float acceleration_;
		float deceleration_;

		sf::Sprite &sprite_; //references a sprite passed into the constructor
	};
}