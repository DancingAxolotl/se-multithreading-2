#include "worker.h"
#include <thread>

namespace
{
    void CallSomeUglyAPI()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    int GetProgressAmount(int progress)
    {
        return 10 * (progress + 1);
    }

    bool IsFinalPieceOfWork(int progress)
    {
        return GetProgressAmount(progress) == 100;
    }
}

Demo::Worker::Worker()
    : QObject(nullptr)
    , m_interrupted(false)
{
    connect(this, &Demo::Worker::Work, this, &Demo::Worker::DoWork, Qt::QueuedConnection);
}

void Demo::Worker::StartWork()
{
    m_interrupted = false;
    emit Work(0, QPrivateSignal());
}

void Demo::Worker::StopWork()
{
    m_interrupted = true;
}

void Demo::Worker::DoWork(int progress)
{
    if (!m_interrupted)
    {
        CallSomeUglyAPI();
        emit Progress(GetProgressAmount(progress));

        if (IsFinalPieceOfWork(progress))
        {
            emit Finished();
        }
        else
        {
            emit Work(progress+1, QPrivateSignal());
        }
    }
}
