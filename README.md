# cpp-scope-timer
A lightweight, header-only C++ timer for measuring code execution time using RAII. 
## Quick Example
```cpp
{
    Timer<Timer_Aliases::ms> timer("Some Operation");
    // your code here
} // automatically prints: [Some Operation] Took: 42ms
```
## Manual Timer
```cpp
{
ManualTimer<Timer_Aliases::ms> manualTimer ("Manual Timer");
while(true)
{
manualTimer.StartTimer();
// your code here
manualTimer.StopTimer();
}// automatically prints: [Manual Timer] Took: 42ms
```
## Passing custom function for logging
```cpp
{
    void CustomLog(const char* name, int64_t amount,const char* type)
    {
        // your code here
    }
    void foo()
    {
      Timer<Timer_Aliases::ms> timer("Some Operation",CustomLog);
        // your code here
    } // automatically prints: [Some Operation] Took: 42ms
}
```
