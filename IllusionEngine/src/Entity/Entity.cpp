#include "Entity.h"

namespace Illusion
{
	Entity::Entity()
	{
		this->_texture = nullptr;
		this->_movement = nullptr;
		this->_animation = nullptr;
	}

	Entity::~Entity()
	{
		delete this->_movement;
		delete this->_animation;
	}

	void Entity::__setTexture(sf::Texture &tex)
	{
		this->_texture = &tex;
		this->_sprite.setTexture(tex);
	}

	void Entity::createMovementComponent(float maxVelocity, float acceleration, float deceleration)
	{
		_movement = new MovementComponent(this->_sprite, maxVelocity, acceleration, deceleration);
	}

	void Entity::createAnimationComponent(sf::Texture &textureSheet)
	{
		_animation = new AnimationComponent(this->_sprite, textureSheet);
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

	void Entity::__setPosition(const sf::Vector2f pos)
	{
		this->_sprite.setPosition(pos);
	}
	void Entity::__setScale(const sf::Vector2f scale)
	{
		_sprite.setScale(scale);
	}
}