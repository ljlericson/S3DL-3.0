#define DR_WAV_IMPLEMENTATION
#include "Source.h"

namespace Core
{
    namespace Audio
    {
        Source::Source(glm::vec3 pos, const char* audioFpath)
        {
            drwav_int16* pcmData;
            uint32_t channels, sampleRate;
            drwav_uint64 totalPCMframeCount;
            pcmData = drwav_open_file_and_read_pcm_frames_s16(audioFpath, &channels, &sampleRate, &totalPCMframeCount, nullptr);
            if (!pcmData)
                std::print("ERROR: Could not load pcm audio data: {}", audioFpath);

            // loaded our pcm data now we can use it with OpenAl
            alGenBuffers(1, &m_bufferID);
            alBufferData(m_bufferID,
                channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16,
                pcmData,
                ALsizei(totalPCMframeCount * channels * sizeof(drwav_int16)),
                sampleRate);
        }
    }
}