#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QMutex>
// Reference: https://stackoverflow.com/questions/4897912/how-to-properly-interrupt-a-qthread-infinite-loop

 class WorkerThread : public QThread {
     Q_OBJECT
    public:
     WorkerThread(QObject *pointer = nullptr){};
     bool keepRunning;
     void run() override;

    signals:
     void threadStopped();
     void updatePlot(double x, double y);
    private:
     QMutex qmutex;
 };

//class Worker : public QObject {
//    Q_OBJECT

//   public slots:
//    void run();

//   signals:
//    void threadStopped();
//    void updatePlot(double x, double y);

//   private:
//};

//class Controller : public QObject {
//    Q_OBJECT
//    QThread workerThread;

//   public:
//    bool getAbort();
//    Controller() {
//        Worker *worker = new Worker;
//        worker->moveToThread(&workerThread);
//        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
//        connect(this, &Controller::run, worker, &Worker::run);
//        connect(worker, &Worker::threadStopped, this, &Controller::threadStopped);
//        workerThread.start();
//    }
//    ~Controller() {
//        workerThread.quit();
//        workerThread.wait();
//    }
//   public slots:
//    void setAbort(bool a);
//    void threadStopped();
//   signals:
//    void run();

//   private:
//    bool abort = false;
//};

#endif  // WORKERTHREAD_H
