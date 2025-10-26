#define DR_WAV_IMPLEMENTATION
#include "Source.h"

namespace Core
{
    namespace Audio
    {
        Source::Source(Manager::AssetManager* assetManager, const char* fpath, glm::vec3 pos)
            : pos(pos), mrp_bufferManager(assetManager->getAudioBufferManager())
        {
            m_bufferID = mrp_bufferManager->newBufferOrReference(fpath);

            if(m_bufferID != 0)
            {
                alGenSources(1, &m_id);
                alSourcei(m_id, AL_BUFFER, m_bufferID);
                alSource3f(m_id, AL_POSITION, this->pos.x, this->pos.y, this->pos.z);
                // just hardcoding for now
                alSourcef(m_id, AL_GAIN, 1.0f);
                alSource3f(m_id, AL_DIRECTION, 0.0f, 0.0f, 0.0f);
                alSource3f(m_id, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
                alSourcei(m_id, AL_SOURCE_RELATIVE, AL_FALSE);
                alSourcef(m_id, AL_ROLLOFF_FACTOR, 0.1f);
                alSourcef(m_id, AL_REFERENCE_DISTANCE, 15.0f);  // Distance at which volume is full
                alSourcef(m_id, AL_MAX_DISTANCE, 1000.0f);      // Distance after which volume stays constant           
            }
        }

        Source::~Source()
        {
            if(m_bufferID != 0) // won't exist if it is 0
                mrp_bufferManager->removeReference(m_id);

            if (m_id != 0)
                alDeleteSources(1, &m_id);
		}

        void Source::play(uint8_t volume) const
        {
            if (m_id != 0)
            {
                ALint sourceState;
                alGetSourcei(m_id, AL_SOURCE_STATE, &sourceState);
                if(sourceState != AL_PLAYING)
                    alSourcePlay(m_id);
                // update position
                alSource3f(m_id, AL_POSITION, pos.x, pos.y, pos.z);

                // check for errors
                ALenum error = alGetError();
                if (error != AL_NO_ERROR)
                {
                    std::cout << "OpenAL error: " << error << '\n';
                }
            }
            else
                CORE_AUDIO_ERR_LOG("source::play m_id == 0 (invalidated state)");
        }
    }
}