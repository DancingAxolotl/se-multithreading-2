#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worker.h"

Demo::MainWindow::MainWindow() :
    QMainWindow(nullptr),
    m_ui(new Ui::MainWindow())
{
    m_ui->setupUi(this);
    connect(m_ui->startBtn, &QPushButton::clicked, this, &MainWindow::OnStart);
    connect(m_ui->cancelBtn, &QPushButton::clicked, this, &MainWindow::OnCancel);
}

void Demo::MainWindow::OnStart()
{
    if (m_worker == nullptr) {
        m_worker = new Worker(this);
        connect(m_worker, &Worker::Progress, this, &MainWindow::OnProgress);
        connect(m_worker, &Worker::finished, this, &MainWindow::OnFinished);
        connect(m_worker, &Worker::finished, m_worker, &QObject::deleteLater);
        m_worker->start();
        m_ui->progressStatusLabel->setText("Started");
    }
}

void Demo::MainWindow::OnCancel()
{
    if (m_worker != nullptr && m_worker->isRunning()) {
        m_worker->requestInterruption();
        m_ui->progressStatusLabel->setText("Canceled");
    }
}

void Demo::MainWindow::OnProgress(int progress)
{
    m_ui->progressBar->setValue(progress);
}

void Demo::MainWindow::OnFinished()
{
    m_ui->progressStatusLabel->setText("Finished");
    m_worker = nullptr;
}

Demo::MainWindow::~MainWindow() {
    if (m_worker != nullptr) {
        m_worker->requestInterruption();
        if (!m_worker->wait(5000)) {
            m_worker->terminate();
            m_worker->wait();
        }
    }
    delete m_ui;
}
