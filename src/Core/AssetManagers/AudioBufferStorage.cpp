#include "AudioBufferStorage.h"

namespace Core
{
	namespace Manager
	{
		// Makes a new buffer if one doesn't exist otherise in which case it returns the id of the pre-existing buffer
		ALuint AudioBufferManager::newBufferOrReference(const char* fpath)
		{
			std::string fpathStr{ fpath };
			if (!m_buffers.contains(fpathStr))
			{
				auto buffer = std::make_unique<AudioBuffer>(fpath);
				ALuint bufferID = buffer->id; // avoid use after std::move
				if(bufferID != 0)
				{
					m_buffers.insert({
						fpathStr,
						std::move(buffer)
					});
					m_idToString.insert({
						bufferID,
						fpath
					});
					m_refCounts.insert({
						fpathStr,
						1
					});
				}
				return bufferID;
			}
			else
			{
				std::print("INFO: Found existing audio buffer...");
				ALuint bufferID = m_buffers.at(fpathStr)->id;
				m_refCounts.at(fpathStr)++;
				return bufferID;
			}
		}

		void AudioBufferManager::removeReference(ALuint id)
		{
			if (m_idToString.contains(id))
			{
				const std::string& key = m_idToString.at(id);
				m_idToString.erase(id);
				if (--m_refCounts.at(key) == 0) // we know it must exist in ref count map
				{
					m_refCounts.erase(key);
					m_buffers.erase(key);
				}
			}
			else std::println("WARNING: No buffer found with given ID (AudioBufManager::removeReference");
		}

		void AudioBufferManager::clear()
		{
			m_buffers.clear();
			m_idToString.clear();
			m_refCounts.clear();
		}

		AudioBufferManager::AudioBuffer::AudioBuffer(const char* fpath)
		{
			drwav_int16* pcmData;
			uint32_t channels, sampleRate;
			drwav_uint64 totalPCMframeCount;
			pcmData = drwav_open_file_and_read_pcm_frames_s16(fpath, &channels, &sampleRate, &totalPCMframeCount, nullptr);
			if (!pcmData)
			{
				std::println("ERROR: Could not load pcm audio data: {}", fpath);
			}
			else
			{
				// loaded our pcm data now we can use it with OpenAl
				alGenBuffers(1, &id);
				alBufferData(
					id,
					channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16,
					pcmData,
					ALsizei(totalPCMframeCount * channels * sizeof(drwav_int16)),
					sampleRate
				);
			}
			drwav_free(pcmData, nullptr);
		}

		AudioBufferManager::AudioBuffer::~AudioBuffer()
		{
			if (id != 0)
				alDeleteBuffers(1, &id);
		}
	}
}