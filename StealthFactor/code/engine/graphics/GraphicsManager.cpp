#include "engine/graphics/GraphicsManager.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <engine/assets/AssetManager.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/graphics/Camera.hpp>
#include <engine/graphics/ShapeListDescriptor.hpp>
#include <engine/graphics/ShapeListInstance.hpp>
#include <engine/frontend/FrontendManager.hpp>
#include <engine/util/Assert.hpp>
#include <engine/Engine.hpp>

namespace engine
{
	namespace graphics
	{
		Manager::Manager(assets::Manager& assetsManager, EventListener& eventListener)
			: _assetsManager{ assetsManager }
			, _eventListener{ eventListener }
		{
		}

		Manager::~Manager()
		{
		}

		bool Manager::setUp()
		{
			_window.create(sf::VideoMode{ (unsigned int)_WINDOW_WIDTH, (unsigned int)_WINDOW_HEIGHT }, "Stealth Factor");

			if (!_window.isOpen())
			{
				return false;
			}

			return true;
		}

		void Manager::tearDown()
		{
			ASSERT(_shapeListInstances.size() == 0);

			_window.close();
		}

		void Manager::pollEvents()
		{
			sf::Event event;
			while (_window.pollEvent(event))
			{
				_eventListener.onEvent(event);
			}
		}

		void Manager::draw()
		{
			_window.clear(sf::Color::Black);

			ASSERT(_activeCamera);
			sf::View view{ _activeCamera->getPosition(), sf::Vector2f{ (float)_WINDOW_WIDTH, (float)_WINDOW_HEIGHT } };
			_window.setView(view);

			for (auto& instance : _shapeListInstances)
			{
				sf::RenderStates renderStates{ instance->transform };
				for (auto& shape : instance->shapeList.getShapes())
				{
					_window.draw(*shape, renderStates);
				}
			}

			_window.display();
		}

		CameraId Manager::createCamera()
		{
			auto camera{ new Camera() };
			_cameras.insert(CameraPtr{ camera });
			return camera;
		}

		void Manager::destroyCamera(CameraId id)
		{
			auto it = std::find_if(
				std::begin(_cameras),
				std::end(_cameras),
				[id](const CameraPtr& camera)
				{
					return camera.get() == id;
				});
			ASSERT(it != std::end(_cameras));
			_cameras.erase(it);
		}

		void Manager::setCameraActive(CameraId id)
		{
			ASSERT(id);
			_activeCamera = id;
		}

		void Manager::setCameraPosition(CameraId id, const sf::Vector2f& position)
		{
			ASSERT(id);
			auto camera = id;
			camera->setPosition(position);
		}

		ShapeListId Manager::createShapeListInstance(const std::string& name)
		{
			auto descriptor{ _assetsManager.getAsset<ShapeListDescriptor>(name) };
			if (!descriptor)
			{
				return nullptr;
			}

			auto instance{ new ShapeListInstance{ *descriptor, sf::Transform() } };
			ShapeListInstancePtr instanceUPtr{ instance };

			_shapeListInstances.insert(std::move(instanceUPtr));
			return instance;
		}

		void Manager::destroyShapeListInstance(ShapeListId id)
		{
			auto it = std::find_if(std::begin(_shapeListInstances), std::end(_shapeListInstances), [id](const ShapeListInstancePtr& instance)
				{
					return instance.get() == id;
				});
			ASSERT(it != std::end(_shapeListInstances));
			_shapeListInstances.erase(it);
		}

		void Manager::setShapeListInstanceMatrix(ShapeListId id, const sf::Transform& matrix)
		{
			// TODO Optimize (kd-tree...)
			ShapeListInstance* instance = id;
			instance->transform = matrix;
		}
	}
}
