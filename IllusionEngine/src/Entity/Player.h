#pragma once
#include "Entity.h"
#include "../Utils/Camera.h"
#include "../Utils/Keyboard.h"

namespace Illusion
{
	class Player : public Entity
	{
	public:
		Player(sf::Texture &texSheet, sf::Vector2f pos);
		~Player();

	public:
		void handleInput(const float &dt)override;
		void update(const float &dt)override;
		void draw(sf::RenderTarget &target)override;

	public:
		void setPosition(const sf::Vector2f pos) { __setPosition(pos); }

	public:
		sf::Sprite &getSprite() { return this->_sprite; }
		sf::FloatRect getBounds()const { return this->_sprite.getGlobalBounds(); }
		sf::Vector2f &getVelocity() { return this->_movement->getVelocity(); }

		const sf::Vector2f getPosition()const override { return _sprite.getPosition(); }

	private:
		void initComponents();
		void initAnimation();

	private:
		Camera *pcamera_;
	};
}