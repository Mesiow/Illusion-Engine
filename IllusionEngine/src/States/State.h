#pragma once
#include "../Gui/Gui.h"
#include "../ResourceManagement/ResourceManager.h"
#include "../Utils/Keyboard.h"


namespace Illusion
{
	class Game;
	class State : public sf::NonCopyable
	{
	public:
		State(Game &game)
			:_game(&game) {}

		virtual ~State() = default;

		virtual void handleInput(){}
		virtual void handleInput(const float &dt){}
		virtual void handleEvents(sf::Event &e){}
		virtual void update(sf::RenderTarget &target){}
		virtual void update(float &dt){}
		virtual void draw(sf::RenderTarget &target) = 0;

		virtual void freeTextures() {}
		virtual void freeFonts(){}
		virtual void freeSoundBuffers(){}

	protected:
		void updateMousePositions();
		void updateMouseGridPosition(int gridDimension);
		void showMouseCoordinates();

	private:
		bool enableMousePos = false;

	protected:
		Game *_game;

	public:
		static sf::Vector2i _mousePosScreen;
		static sf::Vector2f _mousePosView;
		static sf::Vector2i _mousePosWindow;
		static sf::Vector2u _mousePosGrid;
		static sf::Vector2u _mousePosTextureBounds;
	};
}