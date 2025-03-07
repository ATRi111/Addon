#pragma once
#include"GameCycleBase.h"

namespace Tools
{
    class ITimer
    {
    public:
        static GameCycleBase* gameCycle;
        virtual bool Completed() const = 0;
        virtual float Duration() const = 0;
        virtual bool Paused() const = 0;
        virtual float Time() const = 0;
        virtual float Percent() const = 0;
        virtual void Start() = 0;
        virtual void Pause() = 0;
        virtual void Stop() = 0;
        virtual void Restart(bool fixedTime) = 0;
        virtual void ForceComplete() = 0;
    };

    GameCycleBase* ITimer::gameCycle = nullptr;
}