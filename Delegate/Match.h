#pragma once
#include"Delegate.h"
#include"ActionList.h"
#include"FuncList.h"
#include"Action.h"
#include"Func.h"

namespace Tools
{
	template<typename ...Args>
	inline bool Delegate::MatchAction()
	{
		return typeid(*this) == typeid(ActionList<Args...>);
	}
	template<typename TResult, typename ...Args>
	inline bool Delegate::MatchFunc()
	{
		return typeid(*this) == typeid(FuncList<TResult, Args...>);
	}

	inline bool Delegate::Match(Delegate* other) const
	{
		return typeid(*this) == typeid(*other);
	}

	template<typename ...Args>
	inline bool IAction<Args...>::Equal(void(*F)(Args...))
	{
		StaticAction<Args...>* p = dynamic_cast<StaticAction<Args...>*>(this);
		if (p)
			return p->Equal(F);
		return false;
	}

	template<typename ...Args>
	template<typename I>
	inline bool IAction<Args...>::Equal(I* instancePtr, void(I::* F)(Args...))
	{
		MemberAction<I, Args...>* p = dynamic_cast<MemberAction<I, Args...>*>(this);
		if (p)
			return p->Equal(instancePtr, F);
		return false;
	}

	template<typename TResult, typename ...Args>
	inline bool IFunc<TResult, Args...>::Equal(TResult(*F)(Args...))
	{
		StaticFunc<TResult, Args...>* p = dynamic_cast<StaticFunc<TResult, Args...>*>(this);
		if (p)
			return p->Equal(F);
		return false;
	}
	template<typename TResult, typename ...Args>
	template<typename I>
	inline bool IFunc<TResult, Args...>::Equal(I* instancePtr, TResult(I::* F)(Args...))
	{
		MemberFunc<TResult, I, Args...>* p = dynamic_cast<MemberFunc<TResult, I, Args...>*>(this);
		if (p)
			return p->Equal(instancePtr, F);
		return false;
	}
}