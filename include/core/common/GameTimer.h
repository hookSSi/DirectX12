//***************************************************************************************
// GameTimer.h by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#ifndef GAMETIMER_H
#define GAMETIMER_H

namespace Common
{
    class GameTimer
    {
        public:
            GameTimer();

            float TotalTime() const;  // in seconds
            float DeltaTime() const;  // in seconds

            void Reset();  // Call before message loop.
            void Start();  // Call when unpaused.
            void Stop();   // Call when paused.
            void Tick();   // Call every frame.

        private:
            double mSecondsPerCount;
            double mDeltaTime;

            //                     |<--paused time-->|
            // ----*---------------*-----------------*------------*------------*------>
            // time
            //  mBaseTime       mStopTime        startTime     mStopTime    mCurrTime

            __int64 mBaseTime;
            __int64 mPausedTime;
            __int64 mStopTime;
            __int64 mPrevTime;
            __int64 mCurrTime;

            bool mStopped;
    };
}  // namespace Common

#endif  // GAMETIMER_H