#include "../pcHeaders.h"
#include "Player.h"
#include "../Game.h"


namespace Illusion
{
	Player::Player(sf::Texture &texture, const sf::Vector2f &position)
	{
		this->pos = position;
		_texture = &texture;

		_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		_sprite.setTexture(texture);
		_sprite.setPosition(position);
		_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
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
		createAnimationComponent();
	}

	void Player::initAnimation()
	{
		//init animation
		animations_[(int)AnimIndex::Idle] = Animation(ResourceManager::getTexture("player_idle"),0, 0, 48, 32, 17, 0.1f);
		animations_[(int)AnimIndex::WalkRight] = Animation(ResourceManager::getTexture("player_walk"), 0, 0, 56, 48, 20, 0.1f);
		animations_[(int)AnimIndex::WalkLeft] = Animation(ResourceManager::getTexture("player_walk"), 0, 0, 56, 48, 20, 0.1f);
		animations_[(int)AnimIndex::Attack] = Animation(ResourceManager::getTexture("player_attack"), 0, 0, 56, 48, 20, 0.05f);
	}

	void Player::setDir(const sf::Vector2f& dir)
	{
		if (currAnimation_ != AnimIndex::Attack)
		{
			if (dir.x > 0.0f)
			{
				currAnimation_ = AnimIndex::WalkRight;
				_sprite.setScale(1, 1);
			}
			else if (dir.x < 0.0f)
			{
				//walk left
				currAnimation_ = AnimIndex::WalkLeft;
				_sprite.setScale(-1, 1);
			}
			else
			{
				currAnimation_ = AnimIndex::Idle;
				/*if (vel.x > 0.0f)
				{
					currAnimation_ = AnimIndex::StandingRight;
				}
				else if (vel.x < 0.0f)
				{
					currAnimation_ = AnimIndex::StandingLeft;
				}
				else if (vel.y < 0.0f)
				{
					currAnimation_ = AnimIndex::StandingUp;
				}
				else if (vel.y > 0.0f)
				{
					currAnimation_ = AnimIndex::StandingDown;
				}*/
			}
		}
		vel = dir * speed;
	}

	void Player::handleInput(const float &dt)
	{
		if (pcamera_)
			pcamera_->follow(this);

		if (attackTime.isExpired())
			currAnimation_ = AnimIndex::Idle;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			attackTime.reset(sf::seconds(1.0f));
			attackTime.start();
			currAnimation_ = AnimIndex::Attack;
		}

		sf::Vector2f dir = { 0.0f,0.0f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			dir.y -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			dir.y += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			dir.x -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			dir.x += 1.0f;
		}
		setDir(dir);

		//if (sf::Keyboard::isKeyPressed((key)Keyboard::getCurrentKeyBinds().at("mUp")))
		//	this->move(0.0f, -1.0f, dt);
		//else if (sf::Keyboard::isKeyPressed((key)Keyboard::getCurrentKeyBinds().at("mLeft")))
		//	this->move(-1.0f, 0.0f, dt);
		//else if (sf::Keyboard::isKeyPressed((key)Keyboard::getCurrentKeyBinds().at("mDown")))
		//	this->move(0.0f, 1.0f, dt);
		//else if (sf::Keyboard::isKeyPressed((key)Keyboard::getCurrentKeyBinds().at("mRight")))
		//	this->move(1.0f, 0.0f, dt);
	}

	void Player::update(const float &dt)
	{
		pos += vel * dt;
		pcamera_->update(Game::getWindow());

		//_movement->update(dt);
		_hitbox->update();

		animations_[(int)currAnimation_].update(dt);
		animations_[(int)currAnimation_].applyToSprite(_sprite);
		_sprite.setPosition(pos);
	}

	void Player::draw(sf::RenderTarget & target)
	{
		_hitbox->draw(target);
		target.draw(_sprite);
	}

	void Player::addAnimation(const std::string id, thor::FrameAnimation& animation, sf::Time time)
	{
		
	}

}