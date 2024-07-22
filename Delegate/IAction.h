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
		virtual void Invoke(Args... args) const = 0;

		template<typename ... Args_>
		bool Equal(const StaticAction<Args_...>& other) const;

		template<typename I_,typename ... Args_>
		bool Equal(const MemberAction<I_, Args_...>& other) const;
	};

	//represents a static/global function without return value
	template<typename ... Args>
	class StaticAction :public IAction<Args...>
	{
		void(*F)(Args...);
	public:
		StaticAction(void(*F)(Args...))
			:F(F)
		{

		}
		void Invoke(Args... args) const override
		{
			return F(args...);
		}
		bool operator==(const StaticAction<Args...>& other) const
		{
			return F == other.F;
		}
	};

	//represents a member function without return value; I represetns the class of the instance
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
		void Invoke(Args... args) const override
		{
			return (instancePtr->*F)(args...);
		}
		bool operator==(const MemberAction<I, Args...>& other) const
		{
			return F == other.F && instancePtr == other.instancePtr;
		}
	};
}
