#pragma once

#include <engine/graphics/CameraId.hpp>
#include <engine/frontend/Component.hpp>

namespace engine
{
	namespace graphics
	{
		class Manager;
	}

	namespace frontend
	{
		namespace components
		{
			class Camera : public Component
			{
			public:
				Camera(Entity& entity);
				virtual ~Camera();

				void onTransformChange() override;

				void setActive();

			protected:
				graphics::CameraId _cameraId;

				graphics::Manager& getGraphicsManager() const;
			};
		}
	}
}
