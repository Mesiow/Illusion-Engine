#pragma once


namespace Illusion
{
	enum class Code
	{
		DELETE_FAILED = -1,
		DELETE_SUCCESS = 0,
	};
	class ResourceManager
	{
	public:
		static void loadTexture(const std::string &name, const std::string &path)
		{
			sf::Texture tex;
			if (!tex.loadFromFile(path))
				throw("failed to load texture");

			textures[name] = tex;
		}

		static void loadFont(const std::string &name, const std::string &path)
		{
			sf::Font font;
			if (!font.loadFromFile(path))
				throw("failed to load font");

			fonts[name] = font;
		}

		static void loadSound(const std::string &name, const std::string &path)
		{
			sf::SoundBuffer buffer;
			if (!buffer.loadFromFile(path))
				throw("failed to load sound buffer");

			sounds[name] = buffer;
		}


	public:
		static sf::Texture &getTexture(const std::string &name)
		{
			return textures[name];
		}

		static sf::Font &getFont(const std::string &name)
		{
			return fonts[name];
		}

		static sf::SoundBuffer &getSoundBuffer(const std::string &name)
		{
			return sounds[name];
		}

		static Code freeTexture(const std::string &name)
		{
			if (textures.find(name) != textures.end()) //texture found
			{
				textures.erase(name); //erase it
				return Code::DELETE_SUCCESS;
			}
			return Code::DELETE_FAILED;

		}
		static Code freeFont(const std::string &name)
		{
			if (fonts.find(name) != fonts.end())
			{
				fonts.erase(name);
				return Code::DELETE_SUCCESS;
			}
			return Code::DELETE_FAILED;
		}
		static Code freeSoundBuffer(const std::string &name)
		{
			if (sounds.find(name) != sounds.end())
			{
				sounds.erase(name);
				return Code::DELETE_SUCCESS;
			}
			return Code::DELETE_FAILED;
		}

	private:
		static std::unordered_map<std::string, sf::Texture> textures;
		static std::unordered_map<std::string, sf::Font> fonts;
		static std::unordered_map<std::string, sf::SoundBuffer> sounds;

	};
}