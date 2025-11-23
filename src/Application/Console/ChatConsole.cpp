#include "ChatConsole.h"

namespace App
{
    namespace Console
    {
        ChatConsole::ChatConsole()
        {
            m_input.reserve(256);
        }

        void ChatConsole::print(const std::string& msg, ImVec4 color)
        {
            m_messages.push_back({ msg, color, (float)ImGui::GetTime() });
            m_scrollToBottom = true;
        }

        void ChatConsole::draw()
        {
            ImGui::SetNextWindowBgAlpha(0.4f);

            ImGui::Begin("Chat", nullptr,
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_AlwaysAutoResize |
                ImGuiWindowFlags_NoMove);
            auto& io = ImGui::GetIO();
            ImGui::SetWindowPos(ImVec2(io.DisplaySize.x - (10 + (io.DisplaySize.y - 250)), io.DisplaySize.y - 250));

            ImGui::BeginChild("ScrollingRegion", ImVec2(400, 200), true);

            for (auto& msg : m_messages)
                ImGui::TextColored(msg.color, "%s", msg.text.c_str());

            if (m_scrollToBottom)
            {
                ImGui::SetScrollHereY(1.0f);
                m_scrollToBottom = false;
            }

            ImGui::EndChild();

            ImGui::PushItemWidth(400);

            if (ImGui::InputText("##ChatInput", &m_input,
                ImGuiInputTextFlags_EnterReturnsTrue))
            {
                if (!m_input.empty())
                {
                    // make input string lowercase
                    std::transform(m_input.begin(), m_input.end(), m_input.begin(),
                        [](uint8_t c) { return std::tolower(c); }
                    );

                    if (m_input == "exit")
                    {
                        exit(0);
                    }
                    else if (m_input == "clear")
                    {
                        m_messages.clear();
                    }
                    else if (m_input == "zsh")
                    {
                        print(std::string("Apple Zsh v1.4 ~/"), ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                        m_zsh = true;
                    }
                    else if (m_input == "ls ~/desktop/s3dl-3.0/" && m_zsh)
                    {
                        print(std::string("build    src    CMakeLists.txt"), ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                    }
                    else if (m_input == "help")
                    {
                        print(std::string("Help..."), ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                    }
                    else
                    {
                        print(std::string("ERROR: Unknown command \"") + m_input + std::string("\""), ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                    }
                    m_input.clear();
                }

                ImGui::SetKeyboardFocusHere(-1);
            }

            ImGui::PopItemWidth();


            ImGui::End();
        }

        void ChatConsole::clear()
        {
            m_messages.clear();
        }

        void ChatConsole::removeLine(size_t elem)
        {
            m_messages.erase(m_messages.begin() + elem);
        }

        Message& ChatConsole::getMessage(size_t elem)
        {
            return m_messages.at(elem);
        }

        std::pair<std::vector<Message>::const_iterator, 
                  std::vector<Message>::const_iterator> ChatConsole::getMessageIterators() const
        {
            return {
                m_messages.begin(),
                m_messages.end()
            };
        }
	}
}