#include "../pcHeaders.h"
#include "Player.h"
#include "../Game.h"


namespace Illusion
{
	Player::Player(sf::Texture &texSheet, sf::Vector2f pos)
	{
		__setTexture(texSheet);
		__setPosition(pos);
		__setScale(sf::Vector2f(2, 2));
		this->initComponents();
		this->initAnimation();
	}

	Player::~Player()
	{
		delete pcamera_;
	}

	void Player::initComponents()
	{
		pcamera_ = new Camera(sf::FloatRect(sf::FloatRect(0.0f, 0.0f, (float)Game::getWindow().getSize().x, (float)Game::getWindow().getSize().y)));
		createMovementComponent(300.0f, 50.0f, 15.0f);
		createAnimationComponent(*_texture);
		createHitBoxComponent(40.0f, 15.0f, 25.0f, 50.0f);
	}

	void Player::initAnimation()
	{
		/*_animation->addAnimation("IDLE_LEFT", 10.0f, 0, 0, 13, 0, 192, 192);
		_animation->addAnimation("WALK_LEFT", 10.0f, 1, 1, 11, 1, 192, 192);
		_animation->addAnimation("ATTACK", 10.0f, 2, 2, 13, 2, 384, 192);*/
		_animation->addAnimation("IDLE", 5.0f, 0, 0, 17, 0, 48, 32);
	}

	void Player::handleInput(const float &dt)
	{
		if (pcamera_)
			pcamera_->follow(this);

		if (sf::Keyboard::isKeyPressed((key)Keyboard::getCurrentKeyBinds().at("mUp")))
			this->move(0.0f, -1.0f, dt);
		else if (sf::Keyboard::isKeyPressed((key)Keyboard::getCurrentKeyBinds().at("mLeft")))
			this->move(-1.0f, 0.0f, dt);
		else if (sf::Keyboard::isKeyPressed((key)Keyboard::getCurrentKeyBinds().at("mDown")))
			this->move(0.0f, 1.0f, dt);
		else if (sf::Keyboard::isKeyPressed((key)Keyboard::getCurrentKeyBinds().at("mRight")))
			this->move(1.0f, 0.0f, dt);
	}

	void Player::update(const float &dt)
	{
		pcamera_->update(Game::getWindow());
		_movement->update(dt);
		_hitbox->update();

		/*if (_movement->isIdle())
			_animation->play("IDLE", dt);*/
		//else if (_movement->getVelocity().x < 0)
			//_animation->play("WALK_LEFT", dt);
	}

	void Player::draw(sf::RenderTarget & target)
	{
		_hitbox->draw(target);
		target.draw(_sprite);
	}

}