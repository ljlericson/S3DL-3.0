#include "EventDispatcher.h"

namespace App
{
	namespace EventSystem
	{
		template<class T> requires std::is_base_of_v<BasicEvent, T>
		void EventDispatcher::registerObserver(const T& e)
		{
			m_subscribers[typeid(e)].push_back(e);
		}

		template<class T> requires std::is_base_of_v<BasicEvent, T>
		void EventDispatcher::unregisterObserver(const T& e)
		{
			auto it = std::find(m_subscribers.at(typeid(T)).begin(), m_subscribers.at(typeid(T)).end(), e);
			m_subscribers.erase(it);
		}

		template<class T> requires std::is_base_of_v<BasicEvent, T>
		void EventDispatcher::notify()
		{
			auto it = m_subscribers.find(typeid(T));
			if (it == m_subscribers.end())
				return;

			for (const BasicEvent& e : it->second)
				static_cast<const T&>(e).subscribe();
		}
	}
}