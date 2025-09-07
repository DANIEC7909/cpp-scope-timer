# cpp-scope-timer
A lightweight, header-only C++ timer for measuring code execution time using RAII. 
## Quick Example
```cpp
{
    Timer<Timer_Aliases::ms> timer("Some Operation");
    // your code here
} // automatically prints: [Some Operation] Took: 42ms
```
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
