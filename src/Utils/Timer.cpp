#include "Timer.h"

Util::Timer::Timer()
    : m_start(std::chrono::high_resolution_clock::now()) { }

void Util::Timer::reset()
{
    m_start = std::chrono::high_resolution_clock::now();
}

float Util::Timer::sinceStarted()
{
    return std::chrono::duration(std::chrono::high_resolution_clock::now() - m_start).count();
}

Util::Timer Util::Timer::operator=(const Timer& other)
{
    // yes copying is intended here
    m_start = other.m_start;
    return *this;
}