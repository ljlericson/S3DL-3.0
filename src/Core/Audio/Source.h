#pragma once
#include <print>
#include <AL/al.h>
#include <dr_wav.h>
// for position
#include <glm/glm.hpp>

namespace Core
{
	namespace Audio
	{
		class Source
		{
		public:
			Source() = default;
			Source(glm::vec3 pos, const char* audioFpath);

			void play(uint8_t volume);

		private:
			ALuint m_bufferID = 0;
		};
	}
}