#pragma once
#include<unordered_map>
#include<string>
#include"Delegate.h"
#include"ActionList.h"

namespace Tools
{
	class EventSystemCore
	{
	protected:
		std::unordered_map<std::string, Delegate*> events;

		template<typename ...Args>
		bool Check(std::string eventName)
		{
			auto it = events.find(eventName);
			if (it != events.end())
			{
				Delegate* d = (*it).second;
				if (d->MatchAction<Args...>())
					return true;

				std::string message = "Parameters mismatch with the existing event [" + eventName + "]";
				OnLog.Invoke(message);
				return false;
			}

			Delegate* d = new ActionList<Args...>();
			events.emplace(eventName, d);
			return true;
		}
	public:
		//functions to log error message
		ActionList<std::string> OnLog;

		EventSystemCore()
		{
		}
		virtual ~EventSystemCore()
		{
			for (auto& pair : events)
			{
				delete pair.second;
			}
		}

		//subscribe to an event (the event is automatically created on first accessing)
		template<typename ... Args>
		void AddListener(std::string eventName, void(*F)(Args...))
		{
			if (Check<Args...>(eventName))
			{
				ActionList<Args...>* a = dynamic_cast<ActionList<Args...>*>(events[eventName]);
				a->Add(F);
			}
		}
		//subscribe to an event (the event is automatically created on first accessing)
		template<typename I, typename ... Args>
		void AddListener(std::string eventName, I* instancePtr, void(I::* F)(Args...)) 
		{
			if (Check<Args...>(eventName))
			{
				ActionList<Args...>* a = dynamic_cast<ActionList<Args...>*>(events[eventName]);
				a->Add(instancePtr, F);
			}
		}

		//unsubscribe from an event (the event is automatically created on first accessing)
		template<typename ... Args>
		bool RemoveListener(std::string eventName, void(*F)(Args...))
		{
			if (Check<Args...>(eventName))
			{
				ActionList<Args...>* a = dynamic_cast<ActionList<Args...>*>(events[eventName]);
				return a->Remove(F);
			}
			return false;
		}
		//unsubscribe from an event (the event is created automatically on first accessing)
		template<typename I, typename ... Args>
		bool RemoveListener(std::string eventName, I* instancePtr, void(I::* F)(Args...))

		{
			if (Check<Args...>(eventName))
			{
				ActionList<Args...>* a = dynamic_cast<ActionList<Args...>*>(events[eventName]);
				return a->Remove(instancePtr, F);
			}
			return false;
		}

		//an event occurs (the event is automatically created on first accessing)
		template<typename ... Args>
		void Invoke(std::string eventName, Args... args)
		{
			if (Check<Args...>(eventName))
			{
				ActionList<Args...>* a = dynamic_cast<ActionList<Args...>*>(events[eventName]);
				a->Invoke(args...);
			}
		}
	};
}