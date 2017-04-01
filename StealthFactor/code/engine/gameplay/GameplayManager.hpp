#pragma once

#include <set>
#include <string>
#include <SFML/System/Vector2.hpp>

namespace engine
{
	namespace gameplay
	{
		class Entity;

		namespace entities
		{
			class Player;
		}

		class Manager
		{
		public:
			void update();
			void draw();

			void gameOver();

			sf::Vector2f getViewCenter() const;

			void loadMap(const std::string& mapName);
			void loadNextMap();

			const entities::Player& getPlayer() const;

			static const float CELL_SIZE;

			static Manager& getInstance();

		private:
			std::set<Entity*> _entities;
			entities::Player* _playerEntity{};

			// Map
			std::string _currentMapName;
			std::string _nextMapName;
			int _rows{ 0 };
			int _columns{ 0 };

			bool _preventMapCompletion{ false };
			bool _nextMapRequested{ false };

			static Manager* _instance;
		};
	}
}
