#pragma once
#include "Utils/FPS.h"
#include "States/State.h"

//Game class manages and runs all states in the game

#define FPS_LIMIT 60
namespace Illusion
{
	using statePtr = std::unique_ptr<State>;

	struct windowData
	{
		int width, height;
		std::string title;
		bool fullScreen;
	};

	class Game : public sf::NonCopyable
	{
	public:
		Game(const std::string &title);
		~Game();

		void initWindow(const std::string &title);
		void initSupportedKeys();
		void run();


	private:
		void updateDt();
		void pollEvents(sf::Event &e);
		void display();
		void clear();


	public:
		template<typename T, typename...Args>
		void changeState(Args&&...args);

		template<typename T, typename...Args>
		void pushState(Args&&...args);

		void pushState(statePtr newState);

		void pop();
		void exit();


	public:
		static sf::RenderWindow &getWindow() { return *window_; }
		State &getCurrentState() { return *this->states_.back(); } //return current state

		std::string getWindowTitle()const { return wData_.title; }

	private:
		void checkPop();

	public:
		static sf::Clock clock_;

	private:
		std::vector<statePtr> states_;
		statePtr changeStatePtr_;

		static sf::RenderWindow *window_;
		windowData wData_;

		bool popState_ = false;
		bool changeState_ = false;
		bool exitGame_ = false;

		FPS fps;
		float dt_;
	};

	template<typename T, typename ...Args>
	inline void Game::changeState(Args && ...args)
	{
		popState_ = true;
		changeState_ = true;
		changeStatePtr_ = std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename ...Args>
	inline void Game::pushState(Args && ...args)
	{
		pushState(std::make_unique<T>(std::forward<Args>(args)...));
	}
}