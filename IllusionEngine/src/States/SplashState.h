#pragma once
#include "State.h"

namespace Illusion
{
	class MenuState;
	class SplashState : public State
	{
	public:
		SplashState(Engine &game, float time);
		~SplashState();

	public:
		void initSplashScreen();
		void update(float &dt)override;
		void draw(sf::RenderTarget &target)override;

	private:
		void loadResources();
		void freeTextures()override;
		
	private:
		float waitTime_;
		sf::RectangleShape splashScreen_;

		const float transitionTime_ = 1.0f;
		sf::RectangleShape transition_;
		sf::Color transitionColor_;

		sf::Clock clock_;
		sf::Time time_;
	};
}