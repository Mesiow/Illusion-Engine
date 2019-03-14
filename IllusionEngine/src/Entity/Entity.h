#pragma once
#include "../Components/Components.h"

namespace Illusion
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		virtual void handleInput(){}
		virtual void handleInput(const float &dt){}
		virtual void update(const float &dt){}
		virtual void draw(sf::RenderTarget &target) = 0;

	protected:
		void __setTexture(sf::Texture &tex);
		void __setPosition(const sf::Vector2f pos);
		void __setScale(const sf::Vector2f scale);

		//construct components functions
		void createMovementComponent(float maxVelocity, float acceleration, float deceleration);
		void createAnimationComponent(sf::Texture &textureSheet);
		void createColliderComponent(){}
		void createHitBoxComponent(float offsetX, float offsetY, float width, float height);


		void move(const float xdir, const float ydir, const float &dt); //updates velocity of movement component


	protected:
		sf::Sprite _sprite;
		sf::Texture *_texture;

		MovementComponent *_movement;
		AnimationComponent *_animation;
		HitBoxComponent *_hitbox;
	};
}


