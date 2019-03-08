#include "../pcHeaders.h"
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
		delete ResolutionList_;
		delete back_;
		delete apply_;
		delete slider_;
	}

	void Settings::initGui()
	{
		std::vector<std::string> videoModeStrings;

		//convert sf video mode values to string values to be passed into the list
		for (std::size_t i = 1; i < videoModes_.size(); i++)
		{
			videoModeStrings.push_back(
				std::string(std::to_string(videoModes_[i].width) + " x " + std::to_string(videoModes_[i].height))
			);
		}

		ResolutionList_ = new gui::DropDownList(sf::Vector2f(400, 100), videoModeStrings, gui::Size::Small, 0);

		back_ = new gui::Button(sf::Vector2f(90, 540), gui::Size::Small);
		back_->setText("Back", ResourceManager::getFont("rubik"), 20,
			sf::Color(85, 85, 85, 200), sf::Color(120, 120, 120, 220), sf::Color(150, 150, 150, 250));
		back_->setFunction([&]() {
			_game->changeState<MenuState>(*_game);
		});

		apply_ = new gui::Button(sf::Vector2f(700, 540), gui::Size::Small);
		apply_->setText("Apply", ResourceManager::getFont("rubik"), 20,
			sf::Color(85, 85, 85, 200), sf::Color(120, 120, 120, 220), sf::Color(150, 150, 150, 250));
		apply_->setFunction([=]() {

			std::string string = ResolutionList_->getActiveButton()->getString();


			std::string widthStr = util::string::getSubStr(string, "x", 0, //retrieve width string before x delimiter
				util::string::getDelimiterPos(string, "x"));

			std::string heightStr = util::string::getSubStr(string, "x",
				util::string::getDelimiterPos(string, "x") + 2, string.size()); //get height after "x" delimiter


			int resWidth = std::stoi(widthStr);
			int resHeight = std::stoi(heightStr);
		
			_game->getWindow().create(sf::VideoMode(resWidth, resHeight), _game->getWindowTitle(), sf::Style::Default); //re-create the window
			_game->getWindow().setFramerateLimit(FPS_LIMIT);

		});



		slider_ = new gui::Slider(sf::Vector2f(300, 500), sf::Vector2f(15, 30),
			sf::Color(85, 85, 85, 200), sf::Color(120, 120, 120, 220), sf::Color(150, 150, 150, 250));
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

		ResolutionList_->handleEvents(e);

		slider_->handleEvents(e);
	}

	void Settings::draw(sf::RenderTarget &target)
	{
		showMouseCoordinates();
		back_->draw(target);
		apply_->draw(target);

		ResolutionList_->draw(target);

		slider_->draw(target);
	}


	void Settings::updateGui(float &dt)
	{
		back_->update();
		apply_->update();

		ResolutionList_->update();

		slider_->update();
	}
}