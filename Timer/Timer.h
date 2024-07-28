#pragma once
#include <type_traits>
#include"ITimer.h"
#include"ILerp.h"
#include"Delegate.h"

namespace Tools
{
    template<typename TValue, typename TLerp>
    class Timer :ITimer
    {
    private:
        bool paused;
        bool completed;
    protected:
        float time;
        TLerp* Lerp;
        float duration;
        TValue origin, target;
        void Tick(float deltaTime);
        void SetCompleted(bool value);
    public:
        ActionList<TValue> BeforePause;
        ActionList<TValue> BeforeResume;
        ActionList<TValue> AfterCompelete;
        ActionList<TValue> OnTick;

        Timer(TValue origin, TValue target, float duration)
            :origin(origin), target(target), duration(duration), time(0), paused(true), completed(false)
        {
            Lerp = new TLerp();
        }
#pragma region Getter
        bool Completed() const override
        {
            return completed;
        }
        float Duration() const override
        {
            return duration;
        }
        bool Paused() const override
        {
            return paused;
        }
        float Time() const override
        {
            return time;
        }
        float Percent() const override
        {
            float temp = time / duration;
            temp = (std::min)(temp, 1.0f);
            temp = (std::max)(temp, 0.0f);
            return temp;
        }
        TValue Origin() const
        {
            return origin;
        }
        TValue Target() const
        {
            return target;
        }
        TValue Current() const
        {
            return Lerp->Value(origin, target, Percent(), time, duration);
        }
#pragma endregion
        void Start() override
        {
            if (paused)
            {
                paused = false;
                BeforeResume.Invoke(Current());
                gameCycle->AttachToGameCycle(this, &Timer<TValue, TLerp>::Tick);
            }
        }
        void Pause() override
        {
            if (!paused)
            {
                paused = true;
                BeforePause.Invoke(Current());
                gameCycle->RemoveFromGameCycle(this, &Timer<TValue, TLerp>::Tick);
            }
        }
        void Stop() override
        {
            time = 0;
            Pause();
        }
        void Restart(bool fixedTime = true) override
        {
            if (fixedTime)
                time -= duration;
            else
                time = 0;
            Start();
            SetCompleted(false);
        }
        virtual void ForceComplete() override
        {
            time = duration;
            OnTick.Invoke(Current());
            Paused();
            SetCompleted(true);
        }
        virtual void Reset(TValue origin, TValue target, float duration)
        {
            Stop();
            this->origin = origin;
            this->target = target;
            this->duration = duration;
        }
    };

    template<typename TValue, typename TLerp>
    inline void Timer<TValue, TLerp>::Tick(float deltaTime)
    {
        time += deltaTime;
        OnTick.Invoke(Current());
        if (time >= duration)
        {
            Pause();
            SetCompleted(true);
        }
    }

    template<typename TValue, typename TLerp>
    inline void Timer<TValue, TLerp>::SetCompleted(bool value)
    {
        if (completed != value)
        {
            completed = value;
            if (value)
            {
                AfterCompelete.Invoke(Current());
            }
        }
    }
}