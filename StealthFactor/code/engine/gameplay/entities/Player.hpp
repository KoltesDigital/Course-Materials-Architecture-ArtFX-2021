#pragma once

#include <engine/gameplay/entities/Character.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			class Player : public Character
			{
			public:
				Player(EntityContext& context);

				void update() override;

				bool hasJustMoved() const;

			private:
				bool _justMoved{ false };
			};
		}
	}
}
