#include "time_measure.h"

namespace utilities {

    void TimeMeasur::Start()
    {
        start_ = std::chrono::high_resolution_clock::now();
    }



    void TimeMeasur::Stop()
    {
        end_ = std::chrono::high_resolution_clock::now();
    }



    TimeMeasur::nanosecond TimeMeasur::GetTime()
    {
        return end_ - start_;
    }



    void TimeMeasur::Reset()
    {
        start_ = time_point{ nanosecond{ 0} };
        end_ = time_point{ nanosecond{ 0} };
    }
}
