#pragma once
#include <QObject>


namespace Demo {
    class Worker : public QObject
    {
        Q_OBJECT

    public:
        explicit Worker();

    public slots:
        void StartWork();
        void StopWork();

    signals:
        void Progress(int progress);
        void Finished();
        void Work(int progress, QPrivateSignal);

    private slots:
        void DoWork(int progress);

    private:
        bool m_interrupted;
    };
};
