#pragma once
#include <SFML/Graphics.hpp>
namespace Illusion
{
	class Controller : public sf::NonCopyable
	{
	public:
		enum button //xbox controller support
		{
			A = 0, B = 1, X = 2,
			Y = 3, LB = 4, RB = 5,
			BACK = 6, START = 7,
			LJOYSTICKPRESS = 8,
			RJOYSTICKPRESS = 9
		};
		Controller() = default;
		~Controller() = default;

		static bool isConnected();
		static bool isButtonPressed(button pressed);

	private:
		static unsigned int controllerCount_;
	};
}