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

		bool Equal(TResult(*F)(Args...));
		template<typename I>
		bool Equal(I* instancePtr, TResult(I::* F)(Args...));
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
		bool Equal(TResult(*F)(Args...)) const
		{
			return this->F == F;
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
			:F(F), instancePtr(instancePtr)
		{

		}
		TResult Invoke(Args... args) const override
		{
			return (instancePtr->*F)(args...);
		}
		bool Equal(I* instancePtr, TResult(I::* F)(Args...)) const
		{
			return this->instancePtr == instancePtr && this->F == F;
		}
	};
}