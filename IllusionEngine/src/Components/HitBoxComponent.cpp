#include "HitBoxComponent.h"

namespace Illusion
{
	HitBoxComponent::HitBoxComponent(sf::Sprite &sprite, float offsetX, float offsetY, float width, float height)
		:sprite_(sprite), offsetX_(offsetX), offsetY_(offsetY), width_(width), height_(height)
	{
		hitbox_.setPosition(sf::Vector2f(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY));
		hitbox_.setSize(sf::Vector2f(width, height));
		hitbox_.setFillColor(sf::Color::Transparent);
		hitbox_.setOutlineThickness(1.0f);
		hitbox_.setOutlineColor(sf::Color::Green);
	}

	HitBoxComponent::~HitBoxComponent()
	{

	}

	void HitBoxComponent::update()
	{
		hitbox_.setPosition(sf::Vector2f(sprite_.getPosition().x + offsetX_, sprite_.getPosition().y + offsetY_));
	}

	void HitBoxComponent::draw(sf::RenderTarget & target)
	{
		target.draw(hitbox_);
	}

	bool HitBoxComponent::checkCollision(const sf::FloatRect & rect)
	{
		return hitbox_.getGlobalBounds().intersects(rect);
	}
}