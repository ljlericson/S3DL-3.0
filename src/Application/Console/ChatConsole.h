#pragma once
#include <vector>
#include <string>
#include <thread>
#include <imgui.h>
#include "imgui_stdlib.h"
#include "../../Utils/Utils.h"

namespace App
{
	namespace Console
	{
		struct Message
		{
			std::string text;
			ImVec4 color;
			float msgDuration;
		};

		class ChatConsole
		{
		public:
			ChatConsole();

			void print(const std::string& msg, ImVec4 color = ImVec4(1, 1, 1, 1));

			void draw();

			void clear();

			void removeLine(size_t elem);

			Message& getMessage(size_t elem);

			std::pair<std::vector<Message>::const_iterator, 
				      std::vector<Message>::const_iterator> getMessageIterators() const;

		private:

			std::vector<Message> m_messages;
			std::string m_input;
			bool m_scrollToBottom = false;
			bool m_zsh = false;
		};
	}
}