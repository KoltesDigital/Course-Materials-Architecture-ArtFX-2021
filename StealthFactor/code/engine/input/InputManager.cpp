#include "engine/input/InputManager.hpp"

#include <iterator>
#include <engine/graphics/GraphicsManager.hpp>

namespace engine
{
	namespace input
	{
		Manager* Manager::_instance = nullptr;

		bool Manager::isKeyPressed(sf::Keyboard::Key key) const
		{
			if (!graphics::Manager::getInstance().hasFocus())
				return false;

			return sf::Keyboard::isKeyPressed(key);
		}

		bool Manager::isKeyJustPressed(sf::Keyboard::Key key) const
		{
			if (!graphics::Manager::getInstance().hasFocus())
				return false;

			return _justPressedKeys.find(key) != std::end(_justPressedKeys);
		}

		bool Manager::isKeyJustReleased(sf::Keyboard::Key key) const
		{
			if (!graphics::Manager::getInstance().hasFocus())
				return false;

			return _justReleasedKeys.find(key) != std::end(_justReleasedKeys);
		}

		void Manager::clear()
		{
			_justPressedKeys.clear();
			_justReleasedKeys.clear();
		}

		void Manager::onKeyPressed(const sf::Event::KeyEvent& event)
		{
			_justPressedKeys.insert(event.code);
		}

		void Manager::onKeyReleased(const sf::Event::KeyEvent& event)
		{
			_justReleasedKeys.insert(event.code);
		}

		Manager& Manager::getInstance()
		{
			if (!_instance)
				_instance = new Manager();

			return *_instance;
		}
	}
}
