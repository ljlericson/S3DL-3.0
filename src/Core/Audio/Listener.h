#pragma once
#include <print>
#include <AL/al.h>
// for position
#include <glm/glm.hpp>


namespace Core
{
	namespace Audio
	{
		class Listener
		{
		public:
			Listener() = default;
			Listener(glm::vec3 pos);



		public:
			glm::vec3 pos;

		private:
			ALuint m_id = 0;
		};
	}
}