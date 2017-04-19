#pragma once

#include <ode/collision.h>
#include <engine/graphics/ShapeList.hpp>
#include <engine/gameplay/Entity.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			class Target : public Entity
			{
			public:
				Target(EntityContext& context);
				~Target();

				void update() override;

				void draw() override;

			private:
				graphics::ShapeList _shapeList;
				dGeomID _collisionGeomId;
			};
		}
	}
}
