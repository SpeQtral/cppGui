#include "workerThread.h"

#include <chrono>
#include <cmath>
#include <thread>

void WorkerThread::run() {
    qmutex.lock();
    for (int i = 0; i < 15000; i++) {
        emit this->updatePlot(static_cast<double>(i), 0.5*(std::sin(static_cast<double>(i) * 0.1)+1));
        if (this->isInterruptionRequested()) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
    emit this->threadStopped();
    qmutex.unlock();
}

//void Controller::setAbort(bool a) {
//    this->abort = a;
//}

//bool Controller::getAbort() {
//    return this->abort;
//}
