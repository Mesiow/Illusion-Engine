#include "../pcHeaders.h"
#include "TileMap.h"
namespace Illusion
{


	TileMap::TileMap(sf::Texture &sheet, unsigned int width, unsigned int height, int tileWorldDim)
		:sheet_(sheet)
	{
		this->tileWorldDim_ = tileWorldDim;
		this->width_ = width;
		this->height_ = height;
		this->layerCount_ = 0;

		initLayersAndTiles(width, height);

		border_.setSize(sf::Vector2f(float(width * tileWorldDim), float(height * tileWorldDim))); //calculate size of entire map/level
		border_.setPosition(0, 0);
		border_.setFillColor(sf::Color::Transparent);
		border_.setOutlineThickness(1.0f);
		border_.setOutlineColor(sf::Color::Green);
	}

	TileMap::~TileMap()
	{
		freeLayersAndTiles();
	}


	void TileMap::draw(sf::RenderTarget &target)
	{
		target.draw(border_);
		for (std::size_t i = 0; i < layers_.size(); ++i)
		{
			if(layers_[i]!=nullptr)
				layers_[i]->drawTiles(target);
		}
	}

	void TileMap::initLayersAndTiles(unsigned int width, unsigned int height)
	{
		layers_.resize(MAX_LAYERS, nullptr);
		
		//init tiles for the first layer
		layers_[0] = new Layer();
		layers_[0]->initTiles(width, height, 1); //pass in width and height to get the number of tiles for the entire map
		layerCount_++;
	}

	void TileMap::addTile(const sf::Vector2u &position, const sf::IntRect &rect, unsigned short layer)
	{
		if (isInGrid(position))
		{
			int index = getTileIndex(position.x, position.y);
			int layerIndex = layer - 1;

			if (doesLayerExist(layerIndex)) //-1 because it starts at one and we check the index
			{
				if (layers_[layerIndex]->getTiles()[index] == nullptr) //if at a certain layer the tile there is null we can add
				{
					std::cout << "Adding tile to layer: " << layer << std::endl; //add a tile at the specified index according to the grid position passed in
					layers_[layerIndex]->getTiles()[index] = new Tile(sf::Vector2f(float(position.x * tileWorldDim_), float(position.y * tileWorldDim_)),
						sf::Vector2f((float)tileWorldDim_, (float)tileWorldDim_),
						sheet_, rect, sf::Color::White, layer);
				}
			}

		}
	}

	void TileMap::removeTile(const sf::Vector2u &position, unsigned short currentLayer) //remove tile at the current layer we are on
	{	
		if (isInGrid(position))
		{
			//index of tile to delete
			int index = getTileIndex(position.x, position.y);
			int layerIndex = currentLayer - 1; //index of layer
			
			if (layers_[layerIndex]->getTiles()[index] != nullptr)
			{
				std::cout << "removing tile" << std::endl;
				delete layers_[layerIndex]->getTiles()[index];
				layers_[layerIndex]->getTiles()[index] = nullptr;
			}
		}
	}

	void TileMap::addLayer()
	{
		layers_[layerCount_] = new Layer();
		layers_[layerCount_]->initTiles(this->width_, this->height_, layerCount_);
		layerCount_++;
	}

	void TileMap::removeLayer()
	{
		delete layers_[layerCount_ - 1]; //free the layer
		layerCount_--;
	}

	void TileMap::freeLayersAndTiles()
	{
		for (std::size_t i = 0; i < layers_.size(); i++)
		{
			if (layers_[i] != nullptr) //delete if not already null
				delete layers_[i];
		}
	}

	//pass in file to parse data from and store parsed data in DataFormat 
	void TileMap::parseMap(std::ifstream &file, DataFormat &data)
	{
		std::string line;

		auto loadSheet = [&](std::string &value) {
			data.sheetPath = value;
		};

		auto loadWidth = [&](std::string &value) {
			int width = std::stoi(value);
			data.width = width;
		};

		auto loadHeight = [&](std::string &value) {
			int height = std::stoi(value);
			data.height = height;
		};

		auto loadTileDim = [&](std::string &value) {
			int tileDim = std::stoi(value);
			data.tileDim = tileDim;
		};

		auto loadLayerCount = [&](std::string &value) {
			int layerCount = std::stoi(value);
			data.layerCount = layerCount;
		};

		int counter = 0;
		while (std::getline(file, line))
		{
			std::size_t pos = util::string::getDelimiterPos(line, ": ");
			std::string value = util::string::getSubStr(line, ": ", pos + 2, line.size()); //retrieve value after : " in the file

			if (counter == 0)
				loadSheet(value);
			else if (counter == 1)
				loadWidth(value);
			else if (counter == 2)
			{
				loadHeight(value);
				break;
			}

			counter++;
		}

		std::cout << "Sheet: " << data.sheetPath << std::endl;
		std::cout << "Width: " << data.width << std::endl;
		std::cout << "Height: " << data.height << std::endl;
	}

	bool TileMap::loadMap(const std::string &path)
	{
		std::ifstream inFile(path);

		if (!inFile.is_open())
		{
			throw("Failed to load file from " + path);
			return false;
		}

		DataFormat data;
		parseMap(inFile, data);


		inFile.close();

		return true;
	}

	bool TileMap::saveMap(const std::string &name)
	{
		/*
		Saving Format:

		General Data:

		texture sheet,
		width, 
		height,
		tileDimension,
		Layer Count

		Tiles:
		The Tiles' texture rectangle positions

		Rect Left:
		Rect Top:
		Rect Width:
		Rect Height:
		
		*/

		std::ofstream outFile(name);

		if (!outFile.is_open())
		{
			throw(name + "failed to open");
			return false;
		}

		DataFormat data;
		data.sheetPath = "test.png";
		data.width = this->width_;
		data.height = this->height_;
		data.tileDim = this->tileWorldDim_;
		data.layerCount = this->layerCount_;

		if (outFile)
		{
			outFile << "Texture: " << data.sheetPath << "\n" << "Map Width: " << data.width << "\n" << "Map Height: " << data.height << "\n"//write general data into file
				<< "Tile Dimension: " << data.tileDim << "\n" << "Number of layers: " << data.layerCount << "\n\n";

			//write tiles into file
			for (std::size_t i = 0; i < layerCount_; ++i) //loop over layer
			{
				for (std::size_t t = 0; t < layers_[i]->getTiles().size(); ++t) //loop over tiles in that layer
				{
					if (layers_[i]->getTiles()[t] != nullptr)
					{
						const sf::IntRect &rect = layers_[i]->getTiles()[t]->getTileRect();

						outFile << "Rect left: " << rect.left << "\n" << "Rect top: " << rect.top << "\n" << "Rect width: "
							<< rect.width << "\n" << "Rect height: " << rect.height << "\n\n";
					}
				}
			}
		}

		outFile.close();

		return true;
	}


	int TileMap::getTileIndex(int x, int y)
	{
		return (y * width_) + x;
	}

	bool TileMap::isInGrid(const sf::Vector2u & position)
	{
		return (position.x >= 0 && position.x < width_
			&& position.y >= 0 && position.y < height_);
	}

	bool TileMap::doesLayerExist(unsigned int layer)
	{
		return layers_[layer] != nullptr ? true : false;
	}
}
