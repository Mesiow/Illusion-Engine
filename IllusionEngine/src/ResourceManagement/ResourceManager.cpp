#include "../pcHeaders.h"
#include "ResourceManager.h"

namespace Illusion
{
	std::unordered_map<std::string, sf::Texture> ResourceManager::textures;
	std::unordered_map<std::string, sf::Font> ResourceManager::fonts;
	std::unordered_map<std::string, sf::SoundBuffer> ResourceManager::sounds;
}