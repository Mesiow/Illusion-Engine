#pragma once
#include "Entity.h"
#include "../Utils/Camera.h"
#include "../Utils/Keyboard.h"

namespace Illusion
{
	class Player : public Entity
	{
	public:
		Player(sf::Texture &texture, const sf::Vector2f &position);
		~Player();

	public:
		void handleInput(const float &dt)override;
		void update(const float &dt)override;
		void draw(sf::RenderTarget &target)override;

	public:
		sf::Sprite &getSprite() { return this->_sprite; }
		sf::FloatRect getBounds()const { return this->_sprite.getGlobalBounds(); }
		sf::Vector2f &getVelocity() { return this->_movement->getVelocity(); }

		const sf::Vector2f getPosition()const override;

	private:
		void initComponents();
		void initAnimation();

	private:
		Camera *pcamera_;
	};
}