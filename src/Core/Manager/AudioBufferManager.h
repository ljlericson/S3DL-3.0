#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <AL/al.h>
#include <dr_wav.h>

namespace Core
{
	namespace Manager
	{
		class AudioBufferManager
		{
		public:
			AudioBufferManager() = default;

			ALuint newBufferOrReference(const char* fpath);

			void removeReference(ALuint id);

			void clear();

		private:
			struct AudioBuffer
			{
				AudioBuffer(const char* fpath);
				~AudioBuffer();
				ALuint id = 0;
			};

			std::unordered_map<std::string, std::unique_ptr<AudioBuffer>> m_buffers;
			std::unordered_map<ALuint, std::string> m_idToString;
			std::unordered_map<std::string, size_t> m_refCounts;

		};
	}
}