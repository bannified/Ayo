#pragma once

namespace Ayo
{
    class Time
    {
    public:

        static void Initialize();

        static void Update();

        static inline double GetDeltaTime()
        {
            return m_DeltaTime;
        }

    private:
        Time();
        ~Time();

        static double m_DeltaTime;
        static double m_TimeLastFrame;
    };
}

