#include "../pcHeaders.h"
#include "Keyboard.h"

namespace Illusion
{
	supported_keyMap Keyboard::supportedKeys_;
	keyMapBinds Keyboard::currentKeyBinds_;

	void Keyboard::addSupportedKeys(supported_keyMap &map)
	{
		supportedKeys_ = map;
	}

	void Keyboard::addKeyBinds(keyMapBinds &map)
	{
		currentKeyBinds_ = map;
	}

	void Keyboard::printSupportedKeys()noexcept
	{
		if (supportedKeys_.empty())
		{
			std::cout << "key map is empty" << std::endl;
		}
		else
		{
			std::cout << "Supported keys" << std::endl;
			for (auto &key : supportedKeys_)
			{
				std::cout << key.first << ": " << key.second << std::endl;
			}
		}
	}

	void Keyboard::printBoundKeys()noexcept
	{
		std::cout << "Bound keys" << std::endl;
		for (auto &key : currentKeyBinds_)
		{
			std::cout << key.first << ": " << key.second << std::endl;
		}
	}
}
