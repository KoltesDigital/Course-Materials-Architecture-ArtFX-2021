#include "engine/Engine.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <SFML/System.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/input/InputManager.hpp>

namespace engine
{
	Engine* Engine::_instance = nullptr;

	void Engine::loadConfiguration()
	{
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file("configuration.xml");

		if (result)
		{
			assert(!doc.empty());
			auto configuration = doc.first_child();
			_startMap = configuration.child_value("start_map");
		}
		else
		{
			std::cerr << "Configuration parsed with errors." << std::endl;
			std::cerr << "Error description: " << result.description() << std::endl;
			std::cerr << "Error offset: " << result.offset << std::endl;
		}
	}

	void Engine::run()
	{
		_running = true;

		gameplay::Manager::getInstance().loadMap(_startMap);

		sf::Clock clock;
		while (_running)
		{
			_deltaTime = clock.restart().asSeconds();

			physics::Manager::getInstance().update();
			gameplay::Manager::getInstance().update();
			graphics::Manager::getInstance().update();

			graphics::Manager::getInstance().clear();

			gameplay::Manager::getInstance().draw();

			graphics::Manager::getInstance().display();
		}
	}

	float Engine::getDeltaTime() const
	{
		return _deltaTime;
	}

	void Engine::exit()
	{
		_running = false;
	}

	Engine& Engine::getInstance()
	{
		if (!_instance)
			_instance = new Engine();

		return *_instance;
	}
}
