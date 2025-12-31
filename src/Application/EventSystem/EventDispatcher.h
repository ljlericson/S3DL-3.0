#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <algorithm>

#include "BasicEvent.h"
#include "GameStateScanner.h"

namespace App
{
	namespace EventSystem
	{
		class EventDispatcher
		{
			template<class T> requires std::is_base_of_v<BasicEvent, T>
			void registerObserver(const T& e);

			template<class T> requires std::is_base_of_v<BasicEvent, T>
			void unregisterObserver(const T& e);

			template<class T> requires std::is_base_of_v<BasicEvent, T>
			void notify();
		
		private:
			std::unordered_map<
					std::type_index,
					std::vector<std::reference_wrapper<const BasicEvent>>> m_subscribers;

			std::unique_ptr<GameObserverSystem> m_gameObserverSystem;
		};
	}
}