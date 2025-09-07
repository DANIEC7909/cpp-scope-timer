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

template<typename T>
 constexpr const char* ReturnType() 
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
template<typename T>
 void StandardLog(const char* name,std::chrono::duration<double>dur)
{
    std::cout<<"["<< name <<"]"<<"Took: "<< std::chrono::duration_cast<T>(dur).count()<< ReturnType<T>()<<"\n";
}
template<typename T> struct ManualTimer
{
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
    const char* name;
    bool started=false;
    bool stopped=false;
    std::chrono::duration<double> dur;
    ManualTimer(ManualTimer&)=delete;
    ManualTimer(ManualTimer&&)=delete;
    ManualTimer() : startTime(std::chrono::high_resolution_clock::now()),endTime(std::chrono::high_resolution_clock::now()), name("Unknown Timer")
    {
    }
    ManualTimer(const char* timerName) :startTime(std::chrono::high_resolution_clock::now()),endTime(std::chrono::high_resolution_clock::now()), name(timerName)
    {
    }


    void Reset()
    {
        started = false;
        stopped = false;
    }
    void StartTimer()
    {
        if (!started)
            {
            startTime = std::chrono::high_resolution_clock::now();
            started = true;
        }
    }
    void StopTimer()
    {
        if (!stopped)
        {
        endTime = std::chrono::high_resolution_clock::now();
        dur= endTime-startTime;
        StandardLog<T>(name,dur);
        }
    }
    void Display()
    {
        StandardLog<T>(name,dur);
    }

    ~ManualTimer()=default;
};
template<typename T> struct ScopedTimer
{
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
    const char* name;
    ScopedTimer(ScopedTimer&) = delete;
    ScopedTimer(ScopedTimer&&) = delete;
    ScopedTimer() : name("Unknown Timer") , startTime(std::chrono::high_resolution_clock::now())
    {
    }
    ScopedTimer(const char* timerName) : name(timerName), startTime(std::chrono::high_resolution_clock::now())
   {
   }
   ~ScopedTimer()
   {
        endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dur = endTime-startTime;
        StandardLog<T>(name, dur);
   }
};