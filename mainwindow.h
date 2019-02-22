#pragma once
#include <QMainWindow>
#include <memory>

namespace Ui {
    class MainWindow;
};

namespace Demo {
    class Worker;

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow();
        ~MainWindow();

    public slots:
        void OnStart();
        void OnCancel();
        void OnFinished();
        void OnProgress(int progress);

    private:
        Ui::MainWindow* m_ui;
        Worker* m_worker;
    };
};
