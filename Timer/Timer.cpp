#include "Timer.h"

namespace Tools
{
    template<typename TValue, typename TLerp>
    void Timer<TValue, TLerp>::Tick(float deltaTime)
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
    void Timer<TValue, TLerp>::SetCompleted(bool value)
    {
        if (completed != value)
        {
            completed = value;
            if (value)
            {
                AfterCompelete.Invoke(Current);
            }
        }
    }

    template<typename TValue, typename TLerp>
    bool Timer<TValue, TLerp>::Completed() const
    {
        return completed;
    }
    template<typename TValue, typename TLerp>
    float Timer<TValue, TLerp>::Duration() const
    {
        return duration;
    }
    template<typename TValue, typename TLerp>
    bool Timer<TValue, TLerp>::Paused() const
    {
        return paused;
    }
    template<typename TValue, typename TLerp>
    float Timer<TValue, TLerp>::Time() const
    {
        return time;
    }
    template<typename TValue, typename TLerp>
    float Timer<TValue, TLerp>::Percent() const
    {
        float temp = Time() / Duration();
        temp = std::min(temp, 1.0f);
        temp = std::max(temp, 0.0f);
        return temp;
    }
    template<typename TValue, typename TLerp>
    TValue Timer<TValue, TLerp>::Origin() const
    {
        return origin;
    }
    template<typename TValue, typename TLerp>
    TValue Timer<TValue, TLerp>::Target() const
    {
        return target;
    }
    template<typename TValue, typename TLerp>
    TValue Timer<TValue, TLerp>::Current() const
    {
        return Lerp->Value(Origin(), Target(), Percent(), Time(), Duration());
    }
    template<typename TValue, typename TLerp>
    void Timer<TValue, TLerp>::Start()
    {
        if (paused)
        {
            paused = false; 
            BeforeResume.Invoke(Current());
            gameCycle->AttachToGameCycle(this, &Timer<TValue, TLerp>::Tick);
        }
    }
    template<typename TValue, typename TLerp>
    void Timer<TValue, TLerp>::Pause()
    {
        if (!paused)
        {
            paused = true;
            BeforePause.Invoke(Current());
            gameCycle->RemoveFromGameCycle(this, &Timer<TValue, TLerp>::Tick);
        }
    }
    template<typename TValue, typename TLerp>
    void Timer<TValue, TLerp>::Stop()
    {
        time = 0;
        Pause();
    }
    template<typename TValue, typename TLerp>
    void Timer<TValue, TLerp>::ForceComplete()
    {
        time = duration;
        OnTick.Invoke(Current());
        Paused();
        SetCompleted(true);
    }
    template<typename TValue, typename TLerp>
    void Timer<TValue, TLerp>::Restart(bool fixedTime)
    {
        if (fixedTime)
            time -= duration;
        else
            time = 0;
        Start();
        SetCompleted(false);
    }
    template<typename TValue, typename TLerp>
    void Timer<TValue, TLerp>::Reset(TValue origin, TValue target, float duration)
    {
        Stop();
        this->origin = origin;
        this->target = target;
        this->duration = duration;
    }
}