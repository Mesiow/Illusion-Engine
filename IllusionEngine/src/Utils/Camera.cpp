#include "../pcHeaders.h"
#include "Camera.h"
#include "../Entity/Entity.h"

namespace Illusion
{
	Camera::Camera(const sf::FloatRect &viewRect)
	{
		view_.reset(viewRect);
	}

	Camera::~Camera()
	{

	}

	void Camera::update(sf::RenderTarget &target)
	{
		target.setView(view_);
	}

	void Camera::move(const float x, const float y, const float & dt)
	{
		view_.move(x * dt, y * dt);
	}

	void Camera::zoom(float z)
	{
		view_.zoom(z);
	}

	void Camera::follow(Entity *e)
	{
		view_.setCenter(e->getPosition());
	}
}