#pragma once

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

		//check whether the parameters match with ActionList<Args...>
		template<typename ... Args>
		bool MatchAction();

		//check whether the parameters match with FuncList<TResult,Args...>
		template<typename TResult,typename ... Args>
		bool MatchFunc();
	};
}