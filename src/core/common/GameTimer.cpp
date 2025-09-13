#include "core/common/GameTimer.h"

#include <windows.h>

using namespace Common;

GameTimer::GameTimer()
{
    mSecondsPerCount = 0.0;
    mDeltaTime = -1.0;
    mBaseTime = 0;
    mPausedTime = 0;
    mStopTime = 0;
    mPrevTime = 0;
    mCurrTime = 0;
    mStopped = false;

    __int64 countsPerSec;
    QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
    mSecondsPerCount = 1.0 / (double)countsPerSec;
}

/// <summary>
/// 총 경과 시간을 반환합니다.
/// (타이머가 멈춘 동안은 계산하지 않음)
/// </summary>
/// <returns>총 경과 시간</returns>
float GameTimer::TotalTime() const
{
    if (mStopped)
    {
        return (float)(((mStopTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
    }
    else
    {
        return (float)(((mCurrTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
    }
}

float GameTimer::DeltaTime() const { return (float)mDeltaTime; }

void GameTimer::Reset()
{
    __int64 currTime;
    QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

    mBaseTime = currTime;
    mPrevTime = currTime;
    mStopTime = 0;
    mStopped = false;
}

void GameTimer::Start()
{
    __int64 startTime;
    QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

    if (mStopped)
    {
        mPausedTime += (startTime - mStopTime);

        mPrevTime = startTime;
        mStopTime = 0;
        mStopped = false;
    }
}

void GameTimer::Stop()
{
    if (!mStopped)
    {
        __int64 currTime;
        QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

        mStopTime = currTime;
        mStopped = true;
    }
}

void GameTimer::Tick()
{
    if (mStopped)
    {
        mDeltaTime = 0.0;
        return;
    }

    __int64 currTime;
    QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
    mCurrTime = currTime;

    mDeltaTime = (currTime - mPrevTime) * mSecondsPerCount;

    mPrevTime = mCurrTime;

    // deltaTime이 음수가 되는 경우가 있으므로 그 경우를 방지
    if (mDeltaTime < 0.0)
    {
        mDeltaTime = 0.0;
    }
}