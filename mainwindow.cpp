#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCloseEvent>

Demo::MainWindow::MainWindow()
    : QMainWindow(nullptr)
    , m_ui(new Ui::MainWindow())
    , m_workerThread(new QThread())
{
    m_ui->setupUi(this);
    connect(m_ui->startBtn, &QPushButton::clicked, this, &MainWindow::OnStartClicked);
    connect(m_ui->cancelBtn, &QPushButton::clicked, this, &MainWindow::OnCancelClicked);

    Worker* worker = new Worker();
    worker->moveToThread(&m_workerThread);
    connect(worker, &Worker::Progress, this, &MainWindow::OnProgress, Qt::QueuedConnection);
    connect(worker, &Worker::Finished, this, &MainWindow::OnFinished, Qt::QueuedConnection);
    connect(this, &MainWindow::StartWork, worker, &Worker::StartWork, Qt::QueuedConnection);
    connect(this, &MainWindow::StopWork, worker, &Worker::StopWork, Qt::QueuedConnection);
    connect(&m_workerThread, &QThread::finished, worker, &QObject::deleteLater);

    m_workerThread.start();
}

void Demo::MainWindow::OnStartClicked()
{
    emit StartWork();
    m_ui->progressStatusLabel->setText("Started");
    m_ui->startBtn->setEnabled(false);
}

void Demo::MainWindow::OnCancelClicked()
{
    emit StopWork();
    m_ui->progressStatusLabel->setText("Canceled");
    m_ui->startBtn->setEnabled(true);
}

void Demo::MainWindow::OnProgress(int progress)
{
    m_ui->progressBar->setValue(progress);
}

void Demo::MainWindow::OnFinished()
{
    m_ui->progressStatusLabel->setText("Finished");
    m_ui->startBtn->setEnabled(true);
}

void Demo::MainWindow::closeEvent(QCloseEvent* event)
{
    emit StopWork();
    m_workerThread.quit();
    if (!m_workerThread.wait(500)) {
        m_workerThread.terminate();
        m_workerThread.wait();
    }
    event->accept();
}

Demo::MainWindow::~MainWindow()
{
    delete m_ui;
}
