#pragma once
#include <type_traits>
#include"ITimer.h"
#include"ILerp.h"
#include"Delegate.h"
#include"GameCycleBase.h"

namespace Tools
{
    template<typename TValue, typename TLerp>
    class Timer :ITimer
    {
    protected:
        GameCycleBase* gameCycle;
        bool paused;
        bool completed;
        float time;
        ILerp<TValue>* Lerp;
        float duration;
        TValue origin, target;
        void Tick(float deltaTime);
        void SetCompleted(bool value);
    public:
        Action<TValue> BeforePause;
        Action<TValue> BeforeResume;
        Action<TValue> AfterCompelete;
        Action<TValue> OnTick;
        bool Completed() const override;
        float Duration() const override;
        bool Paused() const override;
        float Time() const override;
        float Percent() const override;
        TValue Origin() const;
        TValue Target() const;
        TValue Current() const;
        void Start() override;
        void Pause() override;
        void Stop() override;
        void Restart(bool fixedTime) override;
        virtual void ForceComplete() override;
        virtual void Reset(TValue origin, TValue target, float duration);
    };
}