#include "../pcHeaders.h"
#include "Player.h"
#include "../Game.h"


namespace Illusion
{
	Player::Player(sf::Texture &texture, const sf::Vector2f &position)
	{

		_texture = &texture;

		_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		_sprite.setTexture(texture);
		_sprite.setPosition(position);
		_sprite.setScale(sf::Vector2f(2, 2));
		this->initAnimation();
		this->initComponents();
	}

	Player::~Player()
	{
		delete pcamera_;
	}

	const sf::FloatRect Player::getGlobalBounds() const //return bounds of the players hitbox
	{
		return _hitbox->getBounds();
	}

	const sf::Vector2f Player::getPosition() const
	{
		return sf::Vector2f(_sprite.getPosition().x + _sprite.getGlobalBounds().width / 2,
			_sprite.getPosition().y + _sprite.getGlobalBounds().height / 2); //returns center of player
	}

	void Player::initComponents()
	{
		pcamera_ = new Camera(sf::FloatRect(sf::FloatRect(0.0f, 0.0f, (float)Game::getWindow().getSize().x, (float)Game::getWindow().getSize().y)));
		createMovementComponent(300.0f, 50.0f, 15.0f);
		createHitBoxComponent(40.0f, 15.0f, 25.0f, 50.0f);
		createAnimationComponent(animations_);
	}

	void Player::initAnimation()
	{

		float du = 1.0f;
		//idle(_sprite, 0.0f);
		for (int i = 0; i < 18; i++)
		{
			idle.addFrame(du, sf::IntRect(i * 32 ,0, 32, 32));
			du += 1.0f;
		}
	

		addAnimation("idle", idle, sf::seconds(1.0f));
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

		_animator->update(Game::clock_.restart());
		_animator->animate(_sprite);
	}

	void Player::draw(sf::RenderTarget & target)
	{
		_hitbox->draw(target);
		target.draw(_sprite);
	}

	void Player::addAnimation(const std::string id, thor::FrameAnimation& animation, sf::Time time)
	{
		animations_.addAnimation(id, animation, time);
	}

}