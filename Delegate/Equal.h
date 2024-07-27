#pragma once
#include"Delegate.h"
#include"Func.h"
#include"IFunc.h"
#include"Action.h"
#include"IAction.h"

namespace Tools
{
	template<typename TResult, typename ... Args>
	template<typename TResult_, typename ... Args_>
	inline bool IFunc<TResult, Args...>::Equal(const StaticFunc<TResult_, Args_...>& other) const
	{
		const StaticFunc<TResult_, Args_...>* p = dynamic_cast<const StaticFunc<TResult_, Args_...>*>(this);
		if (p)
			return p->operator==(other);
		return false;
	}

	template<typename TResult, typename ... Args>
	template<typename I_, typename TResult_, typename ... Args_>
	inline bool IFunc<TResult, Args...>::Equal(const MemberFunc<I_, TResult_, Args_...>& other) const
	{
		const MemberFunc<I_, TResult_, Args_...>* p = dynamic_cast<const MemberFunc<I_, TResult_, Args_...>*> (this);
		if (p)
			return p->operator==(other);
		return false;
	}


	template<typename ...Args>
	template<typename ...Args_>
	inline bool IAction<Args...>::Equal(const StaticAction<Args_...>& other) const
	{
		const StaticAction<Args_...>* p = dynamic_cast<const StaticAction<Args_...>*>(this);
		if (p)
			return p->operator==(other);
		return false;
	}

	template<typename ...Args>
	template<typename I_, typename ...Args_>
	inline bool IAction<Args...>::Equal(const MemberAction<I_, Args_...>& other) const
	{
		const MemberAction<I_, Args_...>* p = dynamic_cast<const MemberAction<I_, Args_...>*> (this);
		if (p)
			return p->operator==(other);
		return false;
	}

	template<typename ...Args>
	inline bool Delegate::MatchAction()
	{
		return typeid(*this) == typeid(Action<Args...>);
	}
	template<typename TResult, typename ...Args>
	inline bool Delegate::MatchFunc()
	{
		return typeid(*this) == typeid(Func<TResult, Args...>);
	}

	bool Tools::Delegate::HasSameParameters(Delegate* other) const
	{
		return typeid(*this) == typeid(*other);
	}
}