#pragma once
#include <chrono>

namespace Util
{
    class Timer 
    {
    public:
        
        Timer();

        void reset();

        float sinceStarted();

        Timer operator=(const Timer& other);

    private:
        std::chrono::high_resolution_clock::time_point m_start;
    };
}