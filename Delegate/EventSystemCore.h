#pragma once
#include<unordered_map>
#include<string>
#include"Delegate.h"
#include"Action.h"

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

			Delegate* d = new Action<Args...>();
			events.emplace(eventName, d);
			return true;
		}
	public:
		Action<std::string> OnLog;
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

		template<typename ... Args>
		void AddListener(std::string eventName, void(*F)(Args...))
		{
			if (Check<Args...>(eventName))
			{
				Action<Args...>* a = dynamic_cast<Action<Args...>*>(events[eventName]);
				a->Add(F);
			}
		}
		template<typename I, typename ... Args>
		void AddListener(std::string eventName, I* instancePtr, void(I::* F)(Args...)) 
		{
			if (Check<Args...>(eventName))
			{
				Action<Args...>* a = dynamic_cast<Action<Args...>*>(events[eventName]);
				a->Add(instancePtr, F);
			}
		}

		template<typename ... Args>
		bool RemoveListener(std::string eventName, void(*F)(Args...))
		{
			if (Check<Args...>(eventName))
			{
				Action<Args...>* a = dynamic_cast<Action<Args...>*>(events[eventName]);
				return a->Remove(F);
			}
			return false;
		}
		template<typename I, typename ... Args>
		bool RemoveListener(std::string eventName, I* instancePtr, void(I::* F)(Args...))

		{
			if (Check<Args...>(eventName))
			{
				Action<Args...>* a = dynamic_cast<Action<Args...>*>(events[eventName]);
				return a->Remove(instancePtr, F);
			}
			return false;
		}

		template<typename ... Args>
		void Invoke(std::string eventName, Args... args)
		{
			if (Check<Args...>(eventName))
			{
				Action<Args...>* a = dynamic_cast<Action<Args...>*>(events[eventName]);
				a->Invoke(args...);
			}
		}
	};
}