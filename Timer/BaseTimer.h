#pragma once
#include"Timer.h"
#include"BaseLerp.h"

namespace Tools
{
	template<typename TValue, typename TLerp>
	class Circulation : public Timer<TValue, TLerp>
	{
	protected:
		virtual void AfterComplete_(TValue _)
		{
			TValue temp = this->target;
			this->target = this->origin;
			this->origin = temp;
			this->Restart();
		}
	public:
		Circulation(TValue origin, TValue target, float duration)
			:Timer<TValue, TLerp>(origin, target, duration)
		{
			this->AfterCompelete.Add(this, &Circulation<TValue, TLerp>::AfterComplete_);
		}
	};

	template<typename TValue, typename TLerp>
	class Repeatation : public Timer<TValue, TLerp>
	{
	protected:
		virtual void AfterComplete_(TValue _)
		{
			this->Restart();
		}
	public:
		Repeatation(TValue origin, TValue target, float duration)
			:Timer<TValue, TLerp>(origin, target, duration)
		{
			this->AfterCompelete.Add(this, &Repeatation<TValue, TLerp>::AfterComplete_);
		}
	};

	class Metronome : public Repeatation<float, CurrentTime>
	{
	public:
		Metronome(float duration)
			: Repeatation<float, CurrentTime>(0.0f, duration, duration)
		{

		}
	};

	class TimerOnly : public Timer<float, CurrentTime>
	{
	public:
		TimerOnly(float duration)
			:Timer<float, CurrentTime>(0.0f, duration, duration)
		{

		}
	};

	class LinearTransformation : public Timer<float, FloatLerp>
	{

	};
}