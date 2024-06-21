#include <iostream>
#include <Windows.h>

void SimulateKeyPress() 
{
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

int main()
{

    bool TimerWasStarted = false;
    const auto& ctrl = []() { return GetAsyncKeyState(0x11); };
    const auto& alt = []() { return GetAsyncKeyState(0x12); };
    const auto& S = []() { return GetAsyncKeyState(0x53); };
    const auto& F = []() { return GetAsyncKeyState(0x46); };

    const auto& StartTimer = [ctrl, alt, S]() { return ctrl() && alt() && S(); };
    const auto& StopTimer = [ctrl, alt, F]() { return ctrl() && alt() && F(); };

    while (true) {
        if (StartTimer()) {
            if (!TimerWasStarted) {
                TimerWasStarted = true;
                std::cout << "start" << std::endl;
                for (size_t i = 0; i < 5; i++)
                {
                    std::cout << i << std::endl;
                    Sleep(1000);
                }
                while (!StopTimer())
                {
                    SimulateKeyPress();
                }
            }
        }
        if (StopTimer())
        {
            if (TimerWasStarted) {
                std::cout << "stop" << std::endl;
                TimerWasStarted = false;
                BlockInput(true);
                Sleep(200);
                BlockInput(false);
            }
        }
        Sleep(100);
    }
    return 0;
}