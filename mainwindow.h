#pragma once
#include <QMainWindow>
#include <QThread>
#include "worker.h"

namespace Ui {
    class MainWindow;
};

namespace Demo {
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow();
        virtual ~MainWindow() override;

    public slots:
        void OnStartClicked();
        void OnCancelClicked();
        void OnFinished();
        void OnProgress(int progress);

    signals:
        void StartWork();
        void StopWork();
    protected:
        virtual void closeEvent(QCloseEvent* event) override;

    private:
        Ui::MainWindow* m_ui;
        QThread m_workerThread;
    };
};
