#pragma once
#include"Delegate.h"
#include"Func.h"

namespace Tools
{
	template<typename TResult, typename ... Args>
	template<typename TResult_, typename ... Args_>
	bool IFunc<TResult, Args...>::Equal(const StaticFunc<TResult_, Args_...>& other)
	{
		StaticFunc<TResult_, Args_...>* p = dynamic_cast<StaticFunc<TResult_, Args_...>*>(this);
		if (p)
			return p->operator==(other);
		return false;
	}

	template<typename TResult, typename ... Args>
	template<typename I_, typename TResult_, typename ... Args_>
	bool IFunc<TResult, Args...>::Equal(const MemberFunc<I_, TResult_, Args_...>& other)
	{
		MemberFunc<I_, TResult_, Args_...>* p = dynamic_cast<MemberFunc<I_, TResult_, Args_...>*> (this);
		if (p)
			return p->operator==(other);
		return false;
	}
}