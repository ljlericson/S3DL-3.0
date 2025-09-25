#pragma once
#include <print>
#include <AL/al.h>
#include <dr_wav.h>
// for position
#include <glm/glm.hpp>
#include "../../Utils/Utils.h"
#include "../AssetManagers/AssetManager.h"

namespace Core
{
	namespace Audio
	{
		class Source
		{
		public:
			Source() = default;
			~Source();
			Source(Manager::AssetManager* assetManager, const char* fpath, glm::vec3 pos);

			void play(uint8_t volume) const;

		public:
			glm::vec3 pos;
		private:

			// opengl starts buffer id indexing at 1
			// but i'm not sure about openal so I'm
			// just using UINT_MAX for the time being

			ALuint m_bufferID = UINT_MAX;
			ALuint m_id = UINT_MAX;
		};
	}
}