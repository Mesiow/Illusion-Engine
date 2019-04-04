#pragma once
#include "../Components/Components.h"
#include "../ResourceManagement/ResourceManager.h"

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

	public:
		virtual const sf::Sprite &getSprite() = 0;
		virtual const sf::Vector2f getPosition()const { return sf::Vector2f(); }
		virtual const sf::FloatRect getGlobalBounds()const { return sf::FloatRect(); }

	protected:
		//construct components functions
		void createMovementComponent(float maxVelocity, float acceleration, float deceleration);
		void createColliderComponent(){}
		void createAnimationComponent();
		void createHitBoxComponent(float offsetX, float offsetY, float width, float height);

		void move(const float xdir, const float ydir, const float &dt); //updates velocity of movement component


	protected:
		sf::Sprite _sprite;
		sf::Texture *_texture;

		MovementComponent *_movement;
		HitBoxComponent *_hitbox;
	
	};
}


