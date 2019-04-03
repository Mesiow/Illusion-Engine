#include "../pcHeaders.h"
#include "Entity.h"

namespace Illusion
{
	Entity::Entity()
	{
		this->_texture = nullptr;
		this->_movement = nullptr;
	}

	Entity::~Entity()
	{
		delete this->_movement;
		delete this->_hitbox;
		delete this->_animator;
	}

	void Entity::createMovementComponent(float maxVelocity, float acceleration, float deceleration)
	{
		_movement = new MovementComponent(this->_sprite, maxVelocity, acceleration, deceleration);
	}

	void Entity::createAnimationComponent(thor::AnimationMap<sf::Sprite, std::string> &animationMap)
	{
		_animator = new thor::Animator<sf::Sprite, std::string>(animationMap); //animator takes animations to animate
	}

	void Entity::createHitBoxComponent(float offsetX, float offsetY, float width, float height)
	{
		_hitbox = new HitBoxComponent(this->_sprite, offsetX, offsetY, width, height);
	}

	void Entity::move(const float xdir, const float ydir, const float & dt)
	{
		if (_movement)
		{
			_movement->move(xdir, ydir, dt);
		}
	}
}