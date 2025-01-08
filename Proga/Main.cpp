#include <windows.h>
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<bool> running(false);

void PressKey(WORD key) {
    keybd_event(key, 0, 0, 0);
    Sleep(50);
    keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
}

void PressKeys() {
    while (true) {
        if (running.load()) {
            for (int i = 0; i < 3; ++i) {
                PressKey('E');
                Sleep(100);
            }
            Sleep(500);

            for (int i = 0; i < 2; ++i) {
                PressKey('C');
                Sleep(100);
            }
            Sleep(500);
        }
        else {
            Sleep(100);
        }
    }
}

void CheckKey() {
    while (true) {
        if (GetAsyncKeyState(VK_RSHIFT) & 0x8000) {
            Sleep(200);
            running.store(!running.load());
            if (running.load()) {
                std::cout << "ÐÀÁÎÒÀÅÒ!\n";
            }
            else {
                std::cout << "ÍÅ ÐÀÁÎÒÀÅÒ!\n";
            }
        }
        Sleep(50);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::thread keyChecker(CheckKey);
    std::thread keyPresser(PressKeys);

    keyChecker.join();
    keyPresser.join();

    return 0;
}
