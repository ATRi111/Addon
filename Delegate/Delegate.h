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
		bool HasSameParameters(Delegate* other) const;

		template<typename ... Args>
		bool MatchAction();
		template<typename TResult,typename ... Args>
		bool MatchFunc();
	};
}