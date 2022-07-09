#pragma once
#include <chrono>



namespace utilities {

    class TimeMeasur {
    public:
        using nanosecond = std::chrono::nanoseconds;
        using time_point = std::chrono::steady_clock::time_point;

        // represent num of worker and how much time its take.
        using TimeProcess = std::tuple<int, std::chrono::nanoseconds>;

        void Start();

        void Stop();

        nanosecond GetTime() const;

        void Reset();

    private:
        time_point start_;

        time_point end_;
    };
}
