#pragma once
#include<functional>

namespace Tools
{
	template<typename ... Args>
	class StaticAction;
	template<typename I,typename ... Args>
	class MemberAction;

	//represents any function(including member function) without return value
	template<typename ... Args>
	class IAction
	{
	public:
		virtual void Invoke(Args... args) = 0 const;

		template<typename ... Args_>
		bool Equal(const StaticAction<Args_...>& other) const;

		template<typename I_,typename ... Args_>
		bool Equal(const MemberAction<I_, Args_...>& other) const;
	};

	//represents a static/global function with a return value
	template<typename ... Args>
	class StaticAction :public IAction<Args...>
	{
		void(*F)(Args...);
	public:
		StaticAction(TResult(*F)(Args...))
			:F(F)
		{

		}
		void Invoke(Args... args) override
		{
			return F(args...);
		}
		bool operator==(const StaticAction<Args...>& other)
		{
			return F == other.F;
		}
	};

	//represents a member function with a return value; I_ represetns the class of the instancePtr
	template<typename I, typename ... Args>
	class MemberAction :public IAction<Args...>
	{
		void(I::* F)(Args...);
		I* instancePtr;
	public:
		MemberAction(I* instancePtr, void(I::* F)(Args...))
			:F(F), instancePtr(instancePtr)
		{

		}
		void Invoke(Args... args) override
		{
			return (instancePtr->*F)(args...);
		}
		bool operator==(const MemberAction<I, Args...>& other)
		{
			return F == other.F && instancePtr == other.instancePtr;
		}
	};
}
