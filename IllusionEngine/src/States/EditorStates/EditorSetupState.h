#pragma once
#include "../State.h"
#include "../../Gui/PopUpContainer.h"
#include "../../Gui/DropDownList.h"
#include "../../Utils/UtilityFunctions.h"

namespace Illusion
{
	//state to input all the information like grid size and map size
	class EditorSetupState : public State
	{
	public:
		EditorSetupState(Game &game);
		~EditorSetupState();

	public:
		void update(float &dt)override;
		void handleEvents(sf::Event &e)override;
		void draw(sf::RenderTarget &target)override;

		void updateGui();
		void initGui();
		void initText();


	private:
		std::map<std::string, gui::DropDownList*> options_;

		std::vector<gui::Button> buttons_;
		gui::Button *createButton_;
		gui::Button *backButton_;

		std::vector<sf::Text> optionsTexts_;
		sf::Text mapSizeText_;
		sf::Text tileDimText_;
		sf::Text textureLoadText_;

	};
}