#pragma once
#include <string>
#include <functional>


namespace App
{
	namespace EventSystem
	{
		class EventDispatcher;

		class BasicEvent
		{
		public:
			virtual ~BasicEvent() = default;
			virtual void update() = 0;

		protected:
			EventDispatcher& m_subject;
		};
	}
}