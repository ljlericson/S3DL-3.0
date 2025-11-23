#pragma once
#include "ChatConsole.h"

namespace App
{
	namespace Console
	{
		class ChatStream
		{
		public:
			ChatStream(ChatConsole& console);

			// using std::to_string
			template<typename T>
			ChatStream& operator<<(T value);

			ChatStream& operator<<(char value);

			ChatStream& operator<<(const char* value);

			ChatStream& operator<<(const std::string& value);

			ChatStream& operator<<(std::ostream& (*pf)(std::ostream&));

		private:
			ChatConsole& m_console;
			std::string m_buffer;
		};

		inline ChatConsole cchat;
		inline ChatStream ccout(cchat);
	}
}