#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace engine
{
	namespace graphics
	{
		class ShapeList;

		class Manager
		{
		public:
			Manager();
			~Manager();

			void update();

			void clear();
			void draw(const ShapeList& shapeList, const sf::Transform& transform);
			void display();

			bool hasFocus() const;

			static Manager& getInstance();

		private:
			sf::RenderWindow _window;

			static const sf::Int16 _WINDOW_WIDTH = 800;
			static const sf::Int16 _WINDOW_HEIGHT = 600;

			static Manager* _instance;
		};
	}
}
