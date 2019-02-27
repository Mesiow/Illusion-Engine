#pragma once

namespace Illusion
{
	using keyMapBinds = std::unordered_map<std::string, int>;
	using supported_keyMap = std::unordered_map<std::string, int>;
	using key = sf::Keyboard::Key;

	class Keyboard : public sf::NonCopyable
	{
	public:
		Keyboard() = default;
		~Keyboard() = default;

	public:
		static void addSupportedKeys(supported_keyMap &map);
		static void addKeyBinds(keyMapBinds &map);

	public:
		static void printSupportedKeys()noexcept;
		static void printBoundKeys()noexcept;

	public:
		static supported_keyMap getSupportedKeys() { return supportedKeys_; }
		static keyMapBinds getCurrentKeyBinds() { return currentKeyBinds_; }

	private:
		static supported_keyMap supportedKeys_;
		static keyMapBinds currentKeyBinds_;
	};
}