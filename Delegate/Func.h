#pragma once
#include<functional>
#include<list>

namespace Tools
{
	template<typename TResult, typename ... Args>
	class StaticFunc;
	template<typename I, typename TResult, typename ... Args>
	class MemberFunc;

	//represents any function with a return value
	template<typename TResult,typename ... Args>
	class IFunc
	{
	public:
		virtual TResult Invoke(Args... args) = 0;

		bool Equal(const StaticFunc<TResult, Args...>& other);

		template<typename I>
		bool Equal(const MemberFunc<I, TResult, Args...>& other);
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
		TResult Invoke(Args... args) override
		{
			return F(args...);
		}
		bool operator==(const StaticFunc<TResult, Args...>& other)
		{
			return F == other.F;
		}
	};

	//represents a member function with a return value; I represetns the class of the instancePtr
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
		TResult Invoke(Args... args) override
		{
			return (instancePtr->*F)(args...);
		}
		bool operator==(const MemberFunc<TResult, Args...>& other)
		{
			return F == other.F && instancePtr == other.instancePtr;
		}
	};

	template<typename TResult, typename ... Args>
	inline bool IFunc<TResult, Args...>::Equal(const StaticFunc<TResult, Args...>& other)
	{
		StaticFunc<TResult, Args...>* p = dynamic_cast<StaticFunc<TResult, Args...>*>(this);
		if (p)
			return p->operator==(other);
		return false;
	}

	template<typename TResult, typename ... Args>
	template<typename I>
	bool IFunc<TResult, Args...>::Equal(const MemberFunc<I, TResult, Args...>& other)
	{
		MemberFunc<I, TResult, Args...>* p = dynamic_cast<MemberFunc<I, TResult, Args...>* > (this);
		if (p)
			return p->operator==(other);
		return false;
	}

	//a list of IFunc 
	template<typename TResult, typename ... Args>
	class Func
	{
		std::list<IFunc<TResult, Args...>> funcs;
	public:
		Func()
		{
			funcs = std::list<IFunc<TResult, Args...>>();
		}
		TResult Invoke(Args... args) override
		{
			for (IFunc<TResult, Args...> F : funcs)
			{
				F.Invoke(args...);
			}
		}
	};
}