#pragma once
#include<functional>

namespace Tools
{
	template<typename TResult, typename ... Args>
	class StaticFunc;
	template<typename I, typename TResult, typename ... Args>
	class MemberFunc;

	//represents any function(including member function) with a return value
	template<typename TResult,typename ... Args>
	class IFunc
	{
	public:
		virtual TResult Invoke(Args... args) const = 0;

		template<typename TResult_, typename ... Args_>
		bool Equal(const StaticFunc<TResult_, Args_...>& other) const;

		template<typename I_, typename TResult_, typename ... Args_>
		bool Equal(const MemberFunc<I_, TResult_, Args_...>& other) const;
	};

	//represents a static/global function with a return value
	template<typename TResult, typename ... Args>
	class StaticFunc :public IFunc<TResult, Args...>
	{
		TResult(*F)(Args...);
	public:
		StaticFunc(TResult(*F)(Args...))
			:F(F)
		{

		}
		TResult Invoke(Args... args) const override
		{
			return F(args...);
		}
		bool operator==(const StaticFunc<TResult, Args...>& other) const
		{
			return F == other.F;
		}
	};

	//represents a member function with a return value; I represetns the class of the instance
	template<typename I, typename TResult,typename ... Args>
	class MemberFunc :public IFunc<TResult, Args...>
	{
		TResult(I::*F)(Args...);
		I* instancePtr;
	public:
		MemberFunc(I* instancePtr, TResult(I::* F)(Args...))
			:F(F),instancePtr(instancePtr)
		{

		}
		TResult Invoke(Args... args) const override
		{
			return (instancePtr->*F)(args...);
		}
		bool operator==(const MemberFunc<I, TResult, Args...>& other) const
		{
			return F == other.F && instancePtr == other.instancePtr;
		}
	};
}