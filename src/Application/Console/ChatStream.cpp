#include "ChatStream.h"

namespace App
{
	namespace Console
	{
        ChatStream::ChatStream(ChatConsole & console)
            : m_console(console) {
        }

        template<typename T>
        ChatStream& ChatStream::operator<<(T value)
        {
            m_buffer += std::to_string(value);
            return *this;
        }

        ChatStream& ChatStream::operator<<(char value)
        {
            m_buffer += value;
            return *this;
        }

        ChatStream& ChatStream::operator<<(const std::string& value)
        {
            m_buffer += value;
            return *this;
        }

        ChatStream& ChatStream::operator<<(const char* value)
        {
            m_buffer += value;
            return *this;
        }

        ChatStream& ChatStream::operator<<(std::ostream& (*pf)(std::ostream&))
        {
            // flush on std::endl
            if (pf == static_cast<std::ostream & (*)(std::ostream&)>(std::endl))
            {
                m_console.print(m_buffer);
                m_buffer.clear();
            }
            return *this;
        }

        template ChatStream& ChatStream::operator<< <double>(double);
        template ChatStream& ChatStream::operator<< <float>(float);
        template ChatStream& ChatStream::operator<< <int32_t>(int32_t);
        template ChatStream& ChatStream::operator<< <uint32_t>(uint32_t);
        template ChatStream& ChatStream::operator<< <size_t>(size_t);
	}
}