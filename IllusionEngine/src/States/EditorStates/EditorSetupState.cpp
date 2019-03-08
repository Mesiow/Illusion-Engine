#include "../../pcHeaders.h"
#include "EditorSetupState.h"
#include "../../Game.h"
#include "EditorState.h"

namespace Illusion
{
	EditorSetupState::EditorSetupState(Game &game)
		:State(game)
	{
		initGui();
		initText();
	}

	EditorSetupState::~EditorSetupState()
	{
		for (auto &i : options_)
			delete i.second;

		delete createButton_;
		delete backButton_;
	}

	void EditorSetupState::update(float &dt)
	{
		updateMousePositions();
		updateGui();
	}

	void EditorSetupState::handleEvents(sf::Event &e)
	{
		for (auto &i : options_)
			i.second->handleEvents(e); //handle gui events

		for (auto &b : buttons_)
			b.handleEvents(e);
	}

	void EditorSetupState::draw(sf::RenderTarget &target)
	{
		for (auto &i : options_)
			i.second->draw(target); //draw options gui , drop down list

		for (auto &text : optionsTexts_)
			target.draw(text);

		for (auto &b : buttons_)
			b.draw(target);
	}

	void EditorSetupState::updateGui()
	{
		for (auto &i : options_)
			i.second->update();

		for (auto &b : buttons_)
			b.update();
	}

	void EditorSetupState::initGui()
	{
		const std::vector<std::string> mapSizes{ "64 x 64", "48 x 48", "32 x 32" };
		options_["Map_Sizes"] = new gui::DropDownList(sf::Vector2f(150, 200), mapSizes, gui::Size::Small, 0);


		const std::vector<std::string> gridDimensions{ "32", "16" };
		options_["Grid_Dimensions"] = new gui::DropDownList
		(
			sf::Vector2f(245 + gui::getButtonSize(gui::Size::Small).x, 200),
			gridDimensions, gui::Size::Small, 0
		);


		const std::vector<std::string> sheets{ "Dungeon_Tileset.png" };
		options_["Texture_Sheets"] = new gui::DropDownList
		(
			sf::Vector2f(490 + gui::getButtonSize(gui::Size::Small).x, 200),
			sheets, gui::Size::Small, 0
		);

		createButton_ = new gui::Button(sf::Vector2f(Game::getWindow().getSize().x - 50, Game::getWindow().getSize().y - 50), gui::Size::Small);
		createButton_->setText(std::string("Create"), ResourceManager::getFont("rubik"), 20,
			sf::Color(70, 70, 70, 200), sf::Color(100, 100, 100, 230), sf::Color(150, 150, 150, 255));
		createButton_->setFunction([&]() {

			//Parse out grid width and height and store them in integers to pass into the level Editor

			std::string sizestr = options_["Map_Sizes"]->getActiveButton()->getString();

			std::string widthstr = util::string::getSubStr(sizestr, "x", 0,
				util::string::getDelimiterPos(sizestr, "x"));

			std::string heightstr = util::string::getSubStr(sizestr, "x",
				util::string::getDelimiterPos(sizestr, "x") + 2, sizestr.size());

			int width = std::stoi(widthstr); //convert string to integer
			int height = std::stoi(heightstr);

			//tile dim
			std::string tileDimstr = options_["Grid_Dimensions"]->getActiveButton()->getString();
			int tileDim = std::stoi(tileDimstr);

			//create editor state based on input
			_game->changeState<EditorState>(*_game, width, height, tileDim);
		});

		buttons_.push_back(*createButton_);

		backButton_ = new gui::Button(sf::Vector2f(50, Game::getWindow().getSize().y - 50),
			gui::Size::Small);
		backButton_->setText(std::string("Back"), ResourceManager::getFont("rubik"), 20,
			sf::Color(70, 70, 70, 200), sf::Color(100, 100, 100, 230), sf::Color(150, 150, 150, 255));
		backButton_->setFunction([&]() {
			_game->pop();
		});

		buttons_.push_back(*backButton_);
	}

	void EditorSetupState::initText()
	{
		//Map Size
		mapSizeText_.setFont(ResourceManager::getFont("rubik"));
		mapSizeText_.setString(std::string("Grid Size"));
		mapSizeText_.setCharacterSize(15);
		mapSizeText_.setFillColor(sf::Color(85, 85, 85, 225));

		{
			auto button = options_["Map_Sizes"]->getActiveButton();
			mapSizeText_.setPosition(sf::Vector2f(
				button->getPosition().x + button->getBounds().width / 3.2f,
				button->getPosition().y - button->getBounds().height - 25)
			);
		}
		optionsTexts_.push_back(mapSizeText_);

		//Tile Dim

		tileDimText_ = mapSizeText_;
		tileDimText_.setString(std::string("Tile Dimension"));

		{
			auto button = options_["Grid_Dimensions"]->getActiveButton();
			tileDimText_.setPosition(sf::Vector2f(
				button->getPosition().x + button->getBounds().width / 4.5f,
				button->getPosition().y - button->getBounds().height - 25)
			);
		}
		optionsTexts_.push_back(tileDimText_);

		//Texture

		textureLoadText_ = mapSizeText_;
		textureLoadText_.setString("Texture Sheet");

		{
			auto button = options_["Texture_Sheets"]->getActiveButton();
			textureLoadText_.setPosition(sf::Vector2f(
				button->getPosition().x + button->getBounds().width / 4.5f,
				button->getPosition().y - button->getBounds().height - 25)
			);
		}
		optionsTexts_.push_back(textureLoadText_);
	}
}