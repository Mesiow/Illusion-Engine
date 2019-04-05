#pragma once

namespace Illusion
{
	class HitBoxComponent
	{
	public:
		HitBoxComponent(sf::Sprite &sprite, float offsetX, float offsetY,
			float width, float height);
		~HitBoxComponent();


		void update();
		void draw(sf::RenderTarget &target);

	public:
		void updateOffset(float x, float y);
		bool checkCollision(const sf::FloatRect &rect);

	public:
		sf::FloatRect getBounds()const { return hitbox_.getGlobalBounds(); }
		sf::Vector2f getOffset()const { return sf::Vector2f(offsetX_, offsetY_); }

	private:
		float offsetX_, offsetY_;
		float width_, height_;
		sf::Sprite &sprite_; //reference a sprite to add the hitbox to
		sf::RectangleShape hitbox_;
	};
}