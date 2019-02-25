#include "Settings.h"
#include "../Game.h"
#include "MenuState.h"

namespace Illusion
{
	Settings::Settings(Game &game)
		:State(game)
	{
		initGui();
	}

	Settings::~Settings()
	{
		
	}

	void Settings::initGui()
	{
		list.push_back(std::string("1920 x 1080"));
		list.push_back(std::string("1024 x 720"));
		list.push_back(std::string("800 x 600"));

		list_ = new gui::DropDownList(sf::Vector2f(400, 200), list, gui::Size::small, 0);

		back_ = new gui::Button(sf::Vector2f(90, 540), gui::Size::small);
		back_->setText("Back", ResourceManager::getFont("rubik"), 20,
			sf::Color(85, 85, 85, 200), sf::Color(120, 120, 120, 220), sf::Color(150, 150, 150, 250));
		back_->setFunction([&]() {
			_game->changeState<MenuState>(*_game);
		});

		apply_ = new gui::Button(sf::Vector2f(700, 540), gui::Size::small);
		apply_->setText("Apply", ResourceManager::getFont("rubik"), 20,
			sf::Color(85, 85, 85, 200), sf::Color(120, 120, 120, 220), sf::Color(150, 150, 150, 250));
		apply_->setFunction([&]() {
			std::cout << "Settings applied" << std::endl;
		});
	}

	void Settings::update(float &dt)
	{
		updateMousePositions();
		updateGui(dt);
	}

	void Settings::handleEvents(sf::Event &e)
	{
		back_->handleEvents(e);
		apply_->handleEvents(e);

		list_->handleEvents(e);
	}

	void Settings::draw(sf::RenderTarget &target)
	{
		back_->draw(target);
		apply_->draw(target);

		list_->draw(target);
	}


	void Settings::updateGui(float &dt)
	{
		back_->update();
		apply_->update();

		list_->update();
	}
}