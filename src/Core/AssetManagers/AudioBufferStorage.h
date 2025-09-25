#include <print>
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

			ALuint newBuffer(const char* fpath);

			ALuint tryGetBuffer(const std::string& fpath);

		private:
			struct AudioBuffer
			{
				AudioBuffer(const char* fpath);
				~AudioBuffer();
				ALuint id = UINT_MAX;
			};

			std::unordered_map<std::string, std::unique_ptr<AudioBuffer>> m_buffers;

		};
	}
}