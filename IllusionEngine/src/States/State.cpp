#include "../pcHeaders.h"
#include "State.h"


namespace Illusion
{

	//sf::Vector2i State::_mousePosScreen;
	//sf::Vector2f State::_mousePosView;
	//sf::Vector2i State::_mousePosWindow;
	//sf::Vector2u State::_mousePosGrid;
	//sf::Vector2u State::_mousePosTextureBounds;

	//void State::updateMousePositions()
	//{
	//	this->_mousePosScreen = sf::Mouse::getPosition();
	//	this->_mousePosWindow = sf::Mouse::getPosition(Game::getWindow());
	//	this->_mousePosView = Game::getWindow().mapPixelToCoords(_mousePosWindow); //map pixel on the window to coordinates
	//}

	//void State::updateMouseGridPosition(int gridDimension)
	//{
	//	this->_mousePosGrid.x = (int)this->_mousePosView.x / gridDimension;
	//	this->_mousePosGrid.y = (int)this->_mousePosView.y / gridDimension;
	//}

	//void State::showMouseCoordinates()
	//{

	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	//	{
	//		if (enableMousePos)
	//			enableMousePos = false;
	//		else
	//			enableMousePos = true;
	//	}

	//	if (enableMousePos)
	//	{
	//		//DELETE LATER
	//		sf::Text text;
	//		text.setFillColor(sf::Color::White);
	//		text.setFont(ResourceManager::getFont("rubik"));
	//		text.setCharacterSize(15);
	//		text.setPosition(_mousePosView.x, _mousePosView.y - 50);

	//		std::stringstream ss;
	//		ss << "Window Position: " << _mousePosWindow.x << ", " << _mousePosWindow.y << "\n"
	//			<< "View Position: " << _mousePosView.x << ", " << _mousePosView.y << "\n"
	//			<< "Grid Position: " << _mousePosGrid.x << ", " << _mousePosGrid.y << "\n";

	//		text.setString(ss.str());

	//		_game->getWindow().draw(text);
	//	}
	//}

}