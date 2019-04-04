#pragma once
#include "Entity.h"
#include "../Utils/Camera.h"
#include "../Utils/Keyboard.h"

namespace Illusion
{
	class Player : public Entity
	{

	private:
		enum class AnimIndex
		{
			Idle = 0,
			WalkRight,
			WalkLeft,
			Attack,
			Hurt,
			Die,
			Count
		};
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
		const sf::FloatRect getGlobalBounds()const override;
		sf::Vector2f &getVelocity() { return this->_movement->getVelocity(); }

		const sf::Vector2f getPosition()const override;
		const sf::Sprite &getSprite()override { return this->_sprite; }

	private:
		void initComponents();
		void initAnimation();
		void setDir(const sf::Vector2f& dir);

	private:
		Camera *pcamera_;
		static constexpr float speed = 100.0f;
		sf::Vector2f pos;
		sf::Vector2f vel = { 0.0f, 0.0f };

		Animation animations_[(int)AnimIndex::Count];
		AnimIndex currAnimation_;
		thor::Timer attackTime;
	};
}