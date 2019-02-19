#pragma once
#include "Entity.h"
#include "../Utils/Keyboard.h"
#include "../Utils/Subject.h"

namespace Illusion
{
	class Player : public Entity, public Subject
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

		sf::Sprite &getSprite() { return this->_sprite; }
		sf::FloatRect getBounds()const { return this->_sprite.getGlobalBounds(); }
		sf::Vector2f &getVelocity() { return this->_movement->getVelocity(); }

	private:
		void initComponents();
		void initAnimation();
	};
}