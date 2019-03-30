#pragma once

namespace Illusion
{
	class Entity;
	class Camera
	{
	public:
		Camera(const sf::FloatRect &viewRect);
		~Camera();

		void update(sf::RenderTarget &target);
		void move(const float x, const float y, const float &dt);
		void zoom(float z);

		void follow(Entity *e);

	public:
		const sf::Vector2f &getCenter()const { return view_.getCenter(); }
		const sf::Vector2f &getSize()const { return view_.getSize(); }

	private:
		sf::View view_;
	};
}