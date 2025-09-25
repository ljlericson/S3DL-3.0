#include "AudioBufferStorage.h"

namespace Core
{
	namespace Manager
	{
		// Makes a new buffer if one doesn't exist otherise in which case it returns the id of the pre-existing buffer
		ALuint AudioBufferManager::newBuffer(const char* fpath)
		{
			if (!m_buffers.contains(std::string{ fpath }))
			{
				auto buffer = std::make_unique<AudioBuffer>(fpath);
				ALuint bufferID = buffer->id; // avoid use after std::move
				if(bufferID != UINT_MAX)
				{
					m_buffers.insert({
						std::string(fpath),
						std::move(buffer)
						});
				}
				return bufferID;
			}
			else
			{
				std::print("INFO: Found existing audio buffer...");
				return m_buffers.at(std::string{ fpath })->id;
			}
		}

		AudioBufferManager::AudioBuffer::AudioBuffer(const char* fpath)
		{
			drwav_int16* pcmData;
			uint32_t channels, sampleRate;
			drwav_uint64 totalPCMframeCount;
			pcmData = drwav_open_file_and_read_pcm_frames_s16(fpath, &channels, &sampleRate, &totalPCMframeCount, nullptr);
			if (!pcmData)
			{
				std::print("ERROR: Could not load pcm audio data: {}", fpath);
			}
			else
			{
				// loaded our pcm data now we can use it with OpenAl
				alGenBuffers(1, &id);
				alBufferData(id,
					channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16,
					pcmData,
					ALsizei(totalPCMframeCount * channels * sizeof(drwav_int16)),
					sampleRate);
			}
			drwav_free(pcmData, nullptr);
		}

		ALuint AudioBufferManager::tryGetBuffer(const std::string& fpath)
		{
			if (m_buffers.contains(fpath))
				return m_buffers.at(fpath)->id;
			else
				std::print("WARNING: No buffer found for fpath: {}", fpath);
			
			return UINT_MAX; // not sure if openal starts indexing at 0 or 1
		}

		AudioBufferManager::AudioBuffer::~AudioBuffer()
		{
			if (id != UINT_MAX)
				alDeleteBuffers(1, &id);
		}
	}
}