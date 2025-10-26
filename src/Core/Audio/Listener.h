#pragma once
#include <iostream>
#include <array>
#include <AL/al.h>
#include <AL/alc.h>
// for position
#include <glm/glm.hpp>
#include "../../Utils/Utils.h"


namespace Core
{
	namespace Audio
	{
		class Listener
		{
		public:
			Listener() = default;
			Listener(glm::vec3 pos);
			~Listener();

			void update() const;
		public:
			glm::vec3 pos;
			std::array<float, 6> orientation;
		private:
			ALCdevice* m_device = nullptr;
			ALCcontext* m_context = nullptr;
		};
	}
}