#pragma once
#include <QThread>


namespace Demo {
    class Worker : public QThread
    {
        Q_OBJECT

    public:
        explicit Worker(QObject* parent) : QThread(parent), m_running(false) {}
        virtual void run() override;

    signals:
        void Progress(int progress);

    private:
        bool m_running;
    };
};
