#include "../pcHeaders.h"
#include "Controller.h"

namespace Illusion
{
	unsigned int Controller::controllerCount_ = 0;

	bool Controller::isConnected()
	{
		if (sf::Joystick::isConnected(controllerCount_))
		{
			controllerCount_++;
			return true;
		}
		return false;
	}

	bool Controller::isButtonPressed(button pressed)
	{
		for (std::size_t i = 0; i < controllerCount_; ++i)
		{
			if (sf::Joystick::isButtonPressed(i, pressed))
				return true;
		}
		return false;
	}
}
