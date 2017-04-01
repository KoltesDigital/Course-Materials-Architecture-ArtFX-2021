#include "engine/graphics/GraphicsManager.hpp"

#include <cassert>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Event.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/graphics/ShapeList.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/Engine.hpp>

namespace engine
{
	namespace graphics
	{
		Manager* Manager::_instance = nullptr;

		Manager::Manager()
		{
			_window.create(sf::VideoMode{ (unsigned int)_WINDOW_WIDTH, (unsigned int)_WINDOW_HEIGHT }, "Stealth Factor");

			_window.setVerticalSyncEnabled(true);

			sf::View view(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ (float)_WINDOW_WIDTH, (float)_WINDOW_HEIGHT });
			_window.setView(view);
		}

		Manager::~Manager()
		{
			_window.close();
		}

		void Manager::update()
		{
			input::Manager::getInstance().clear();

			sf::Event event;
			while (_window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					Engine::getInstance().exit();
					break;

				case sf::Event::KeyPressed:
					input::Manager::getInstance().onKeyPressed(event.key);
					break;

				case sf::Event::KeyReleased:
					input::Manager::getInstance().onKeyReleased(event.key);
					break;

				default:
					break;
				}
			}
		}

		void Manager::clear()
		{
			_window.clear(sf::Color::Black);

			sf::View view{ gameplay::Manager::getInstance().getViewCenter(), sf::Vector2f{(float)_WINDOW_WIDTH, (float)_WINDOW_HEIGHT} };
			_window.setView(view);
		}

		void Manager::draw(const ShapeList& shapeList, const sf::Transform& transform)
		{
			sf::RenderStates renderStates{ transform };
			for (auto shape : shapeList.getShapes())
			{
				_window.draw(*shape, renderStates);
			}
		}

		void Manager::display()
		{
			_window.display();
		}

		bool Manager::hasFocus() const
		{
			return _window.hasFocus();
		}

		Manager& Manager::getInstance()
		{
			if (!_instance)
				_instance = new Manager();

			return *_instance;
		}
	}
}
