#pragma once

#include <string>

namespace engine
{
	class Engine
	{
	public:
		void loadConfiguration();

		void run();
		float getDeltaTime() const;

		void exit();

		static Engine& getInstance();

	private:
		bool _running;
		float _deltaTime;

		// Configuration
		std::string _startMap;

		static Engine* _instance;
	};
}
