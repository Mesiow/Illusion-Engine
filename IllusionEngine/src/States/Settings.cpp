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
		delete list_;
		delete back_;
		delete apply_;
		delete slider_;
	}

	void Settings::initGui()
	{
		std::vector<std::string> videoModeStrings;

		//convert sf video mode values to string values to be passed into the list
		for (int i = 1; i < videoModes_.size(); i++)
		{
			videoModeStrings.push_back(
				std::string(std::to_string(videoModes_[i].width) + " x " + std::to_string(videoModes_[i].height))
			);
		}

		list_ = new gui::DropDownList(sf::Vector2f(400, 200), videoModeStrings, gui::Size::small, 0);

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


		slider_ = new gui::Slider(sf::Vector2f(300, 500));
	}

	void Settings::update(float &dt)
	{
		updateMousePositions();
		updateGui(dt);
		showMouseCoordinates();
	}

	void Settings::handleEvents(sf::Event &e)
	{
		back_->handleEvents(e);
		apply_->handleEvents(e);

		list_->handleEvents(e);

		slider_->handleEvents(e);
	}

	void Settings::draw(sf::RenderTarget &target)
	{
		back_->draw(target);
		apply_->draw(target);

		list_->draw(target);

		slider_->draw(target);
	}


	void Settings::updateGui(float &dt)
	{
		back_->update();
		apply_->update();

		list_->update();
	}
}