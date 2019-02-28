#pragma once
#include <QMainWindow>

namespace Ui {
    class MainWindow;
};

namespace Demo {
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow();
        ~MainWindow();

    public slots:
        void OnStartClicked();
        void OnCancelClicked();
        void OnFinished();
        void OnProgress(int progress);

    signals:
        void StartWork();
        void StopWork();

    private:
        Ui::MainWindow* m_ui;
        QThread* m_workerThread;
    };
};
