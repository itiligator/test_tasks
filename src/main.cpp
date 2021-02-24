#include <iostream>
#include "LifeBoard.h"
#include <chrono>
#include <thread>

int main() {
    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.

    LifeBoard lb {34};
    while (true) {
        system("cls");
        lb.PrintToConsole();
        lb.NextStep();
        sleep_for(150ms);
    }
    return 0;
}
