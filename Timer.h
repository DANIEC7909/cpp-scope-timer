#pragma once
#include <chrono>
#include <iostream>
#include <type_traits>
namespace Timer_Aliases {
typedef std::chrono::milliseconds ms;
typedef std::chrono::microseconds us;
typedef std::chrono::nanoseconds ns;
typedef std::chrono::seconds sec;
} // namespace Timer_Aliases

template <typename T> constexpr const char *ReturnType() {
  if constexpr (std::is_same_v<T, Timer_Aliases::us>) {
    return "us";
  }
  if constexpr (std::is_same_v<T, Timer_Aliases::ms>) {
    return "ms";
  }
  if constexpr (std::is_same_v<T, Timer_Aliases::ns>) {
    return "ns";
  }
  if constexpr (std::is_same_v<T, Timer_Aliases::sec>) {
    return "s";
  }
  return "NONE";
}
template <typename T>
void StandardLog(const char *name, int64_t dur, const char *type) {
  std::cout << "[" << name << "]"
            << "Took: " << dur << type << "\n";
}
template <typename T> struct ManualTimer {
private:
  std::chrono::high_resolution_clock::time_point startTime;
  std::chrono::high_resolution_clock::time_point endTime;
  const char *name;
  bool started = false;
  bool stopped = false;

  void (*externalOutput)(const char *, int64_t, const char *type);

  std::chrono::duration<double> dur;

public:
  ManualTimer(ManualTimer &) = delete;
  ManualTimer(ManualTimer &&) = delete;
  ManualTimer()
      : startTime(std::chrono::high_resolution_clock::now()),
        endTime(std::chrono::high_resolution_clock::now()),
        name("Unknown Timer"), externalOutput(StandardLog<T>) {}
  ManualTimer(const char *timerName,
              void (*externalOutpuFunc)(const char *, int64_t,
                                        const char *) = nullptr)
      : startTime(std::chrono::high_resolution_clock::now()),
        endTime(std::chrono::high_resolution_clock::now()), name(timerName),
        externalOutput(externalOutpuFunc == nullptr ? StandardLog<T>
                                                    : externalOutpuFunc) {}

  void Reset() {
    started = false;
    stopped = false;
  }
  void StartTimer() {
    if (!started) {
      startTime = std::chrono::high_resolution_clock::now();
      started = true;
    }
  }
  void StopTimer() {
    if (!stopped) {
      endTime = std::chrono::high_resolution_clock::now();
      dur = endTime - startTime;
      externalOutput(name, std::chrono::duration_cast<T>(dur).count(),
                     ReturnType<T>());
    }
  }
  void Display() {
    externalOutput(name, std::chrono::duration_cast<T>(dur).count(),
                   ReturnType<T>());
  }

  ~ManualTimer() = default;
};
template <typename T> struct ScopedTimer {
private:
  std::chrono::high_resolution_clock::time_point startTime;
  std::chrono::high_resolution_clock::time_point endTime;
  const char *name;
  void (*externalOutput)(const char *, int64_t, const char *type);

public:
  ScopedTimer(ScopedTimer &) = delete;
  ScopedTimer(ScopedTimer &&) = delete;
  ScopedTimer()
      : name("Unknown Timer"),
        startTime(std::chrono::high_resolution_clock::now()),
        externalOutput(StandardLog<T>) {}
  ScopedTimer(const char *timerName,
              void (*externalOutpuFunc)(const char *, int64_t,
                                        const char *) = nullptr)
      : name(timerName), startTime(std::chrono::high_resolution_clock::now()),
        externalOutput(externalOutpuFunc == nullptr ? StandardLog<T>
                                                    : externalOutpuFunc) {}
  ~ScopedTimer() {
    endTime = std::chrono::high_resolution_clock::now();
    externalOutput(name,
                   std::chrono::duration_cast<T>(endTime - startTime).count(),
                   ReturnType<T>());
  }
};
