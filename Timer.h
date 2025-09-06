#pragma once
#include <iostream>
#include <chrono>
#include <type_traits>
namespace Timer_Aliases
{
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::microseconds us;
    typedef std::chrono::nanoseconds ns;
    typedef std::chrono::seconds sec;
}
template<typename T> struct Timer
{
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
    const char* name;
    Timer(Timer&) = delete;
    Timer(Timer&&) = delete;
    Timer() : name("Unknown Timer") , startTime(std::chrono::high_resolution_clock::now())
    {
    }
    Timer(const char* TimerName) : name(TimerName), startTime(std::chrono::high_resolution_clock::now())
   {
    
   }

private:
  constexpr const char* returnType() const
   {
       if constexpr (std::is_same_v<T, Timer_Aliases::us>)
        {
            return "us";
        }
        if constexpr (std::is_same_v<T, Timer_Aliases::ms>)
        {
            return "ms";
        }
        if constexpr (std::is_same_v<T, Timer_Aliases::ns>)
        {
            return "ns";
        }
        if constexpr (std::is_same_v<T, Timer_Aliases::sec>)
        {
            return "s";
        }
        return "NONE";
    }
    public:
   ~Timer()
   {
        endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dur = endTime-startTime;
        std::cout<<"["<< name <<"]"<<"Took: "<< std::chrono::duration_cast<T>(dur).count()<< returnType()<<"\n";
   }
};
