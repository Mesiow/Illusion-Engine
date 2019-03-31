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
		bool checkCollision(const sf::FloatRect &rect);

	public:
		sf::FloatRect getBounds()const { return hitbox_.getGlobalBounds(); }

	private:
		float offsetX_, offsetY_;
		float width_, height_;
		sf::Sprite &sprite_; //reference a sprite to add the hitbox to
		sf::RectangleShape hitbox_;
	};
}