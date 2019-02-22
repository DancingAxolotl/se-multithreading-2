#include "worker.h"

namespace {
    void CallSomeUglyAPI() {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Demo::Worker::run()
{
    m_running = true;
    for (int i = 0; i < 10 && !isInterruptionRequested(); i++)
    {
        CallSomeUglyAPI();
        emit Progress(10*(i+1));
    }
}
