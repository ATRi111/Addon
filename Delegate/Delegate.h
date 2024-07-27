#pragma once
#include <tuple>
#include <typeindex>
#include <typeinfo>

namespace Tools
{
	class Delegate
	{
	protected:
		Delegate()
		{
		}
	public:
		virtual ~Delegate()
		{
		}

		//check whether the parameters match with another Delegate*
		bool Match(Delegate* other) const;

		//check whether the parameters match with Action<Args...>
		template<typename ... Args>
		bool MatchAction();

		//check whether the parameters match with Func<TResult,Args...>
		template<typename TResult,typename ... Args>
		bool MatchFunc();
	};
}