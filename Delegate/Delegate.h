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
		virtual ~Delegate()
		{
			
		}
	public:
		bool HasSameParameters(Delegate* other) const
		{
			return typeid(*this) == typeid(*other);
		}
	};
}