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
		void addAnimation(const std::string id, thor::FrameAnimation& animation, sf::Time time);

	public:
		sf::Sprite &getSprite() { return this->_sprite; }
		const sf::FloatRect getGlobalBounds()const override;
		sf::Vector2f &getVelocity() { return this->_movement->getVelocity(); }

		const sf::Vector2f getPosition()const override;

	private:
		void initComponents();
		void initAnimation();

	private:
		thor::AnimationMap<sf::Sprite, std::string> animations_;
		thor::FrameAnimation idle;
		Camera *pcamera_;
	};
}