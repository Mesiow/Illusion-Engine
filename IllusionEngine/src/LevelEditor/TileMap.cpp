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
		this->tileCount_ = 0;
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
						sheet_, rect, layer);

					tileCount_++;
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

	void TileMap::freeLayersAndTiles()const
	{
		for (std::size_t i = 0; i < layers_.size(); i++)
		{
			if (layers_[i] != nullptr) //delete if not already null
				delete layers_[i];
		}
	}

	//pass in file to parse data from and store parsed data in DataFormat 
	void TileMap::parseMap(std::ifstream &file, MapFormat &data)
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

		auto loadTileNum = [&](std::string &value) {
			int tileNum = std::stoi(value);
			data.tilesInMap = tileNum;
		};

		int counter = 0;
		int end = 6;
		while (std::getline(file, line))
		{
			if (counter != end)
			{
				std::size_t pos = util::string::getDelimiterPos(line, ": ");
				std::string value = util::string::getSubStr(line, ": ", pos + 2, line.size()); //retrieve value after : " in the file

				if (counter == 0)
					loadSheet(value);
				else if (counter == 1)
					loadWidth(value);
				else if (counter == 2)
					loadHeight(value);
				else if (counter == 3)
					loadTileDim(value);
				else if (counter == 4)
					loadTileNum(value);
				else if (counter == 5)
					loadLayerCount(value);
			}
			else if (counter == end) //load in all tiles, its grid position, its rects and layer position
			{
				this->width_ = data.width;
				this->height_ = data.height;
				this->tileWorldDim_ = data.tileDim;
				this->tileCount_ = data.tilesInMap;
				this->layerCount_ = data.layerCount;

				freeLayersAndTiles(); //make room to load
				initLayersAndTiles(width_, height_); //init first layer and tiles

				std::cout << "Layer count: " << data.layerCount << std::endl;
				for (std::size_t i = 0; i < data.layerCount; ++i)
				{
					std::cout << "Layer: " << i << std::endl;
					addLayer();
				}

				for (std::size_t layer = 0; layer < data.layerCount; ++layer) //begin at 1 because layer
				{
					for (std::size_t tile = 0; tile < layers_[layer]->getTiles().size(); ++tile)
					{
						while (file >> data.tileGridPosition.x >> data.tileGridPosition.y >> data.tileRect.left >> data.tileRect.top
							>> data.tileRect.width >> data.tileRect.height >> data.tileLayerNumber)
						{
							addTile(sf::Vector2u(data.tileGridPosition.x, data.tileGridPosition.y), data.tileRect, data.tileLayerNumber); //load the tiles from the file
						}
					}
				}
				break;
			}
			
			counter++;
		}

		std::cout << "Sheet: " << data.sheetPath << std::endl;
		std::cout << "Width: " << data.width << std::endl;
		std::cout << "Height: " << data.height << std::endl;
		std::cout << "Tile Dim: " << data.tileDim << std::endl;
		std::cout << "Tiles in Map: " << data.tilesInMap << std::endl;
		std::cout << "Layers: " << data.layerCount << std::endl;
	}

	bool TileMap::loadMap(const std::string &path)
	{
		std::ifstream inFile(path);

		if (!inFile.is_open())
		{
			throw("Failed to load file from " + path);
			return false;
		}

		MapFormat data;
		parseMap(inFile, data);

		inFile.close();

		return true;
	}

	bool TileMap::saveMap(const std::string &name)
	{
		/*
		Saving Format:

		//////
		General Data:

		Texture sheet,
		Width, 
		Height,
		Tile Dimension,
		Number of of Tiles in Map
		Layer Count

		//////
		Tile Data:

		Tile Position in grid X, Tile Position in grid Y, Rect Left, Rect Top, Rect Width, Rect Height, layer
		
		*/

		std::ofstream outFile(name);

		if (!outFile.is_open())
		{
			throw(name + "failed to open");
			return false;
		}

		MapFormat data;
		data.sheetPath = "test.png";
		data.width = this->width_;
		data.height = this->height_;
		data.tileDim = this->tileWorldDim_;
		data.tilesInMap = this->tileCount_;
		data.layerCount = this->layerCount_;

		if (outFile)
		{
			outFile << "Texture: " << data.sheetPath << "\n" << "Map Width: " << data.width << "\n" << "Map Height: " << data.height << "\n"//write general data into file
				<< "Tile Dimension: " << data.tileDim <<"\n"<< "Tiles in map: "<< data.tilesInMap << "\n" << "Number of layers: " << data.layerCount << "\n";

			//write tiles into file
			for (std::size_t i = 0; i < layerCount_; ++i) //loop over layer
			{
				for (std::size_t t = 0; t < layers_[i]->getTiles().size(); ++t) //loop over tiles in that layer
				{
					if (layers_[i]->getTiles()[t] != nullptr)
					{
						data.tileGridPosition = layers_[i]->getTiles()[t]->getPosition();
						data.tileGridPosition.x /= tileWorldDim_;
						data.tileGridPosition.y /= tileWorldDim_;  //retrieve the grid position of the tile

						const sf::IntRect &rect = layers_[i]->getTiles()[t]->getTileRect();

						outFile << data.tileGridPosition.x << data.tileGridPosition.y << rect.left << rect.top << rect.width << rect.height<<
							layers_[i]->getTiles()[t]->getLayerNumber();
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
