
#include "window.h"

#include "./ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Window) {
    ui->setupUi(this);
    this->series = new QScatterSeries();
    this->series->setUseOpenGL(true);

    this->axisX = new QValueAxis();
    this->axisY = new QValueAxis();
    this->axisX->setRange(0, 1);
    this->axisY->setRange(-1,1);

    this->chart = new QChart();

    this->chart->addAxis(axisX, Qt::AlignBottom);
    this->chart->addAxis(axisY, Qt::AlignLeft);


    this->chart->addSeries(this->series);

    this->series->attachAxis(this->axisX);
    this->series->attachAxis(this->axisY);

    this->chart->setTitle("Testing chart");
    //    this->chart->createDefaultAxes();

    //    this->chart->addAxis(axisY, Qt::AlignBottom);
    this->chart->setTheme(QChart::ChartTheme::ChartThemeDark);

    ui->graphicsView->setChart(this->chart);
}

Window::~Window() {
    delete ui;
}

void Window::startThread() {
    this->workerThread = new WorkerThread(this);
}

void Window::updatePlot(double x, double y) {
    this->series->append(x, y);
    this->axisX->setMax(x);
}

void Window::threadStopped() {
    this->workerThread->wait();
    delete this->workerThread;
    this->workerThread = nullptr;
}

void Window::on_stopButton_clicked() {
    if (this->workerThread != nullptr){
        this->workerThread->requestInterruption();
    }
}

void Window::on_runButton_clicked() {
     this->workerThread = new WorkerThread(this);
     connect(this->workerThread, &WorkerThread::updatePlot, this, &Window::updatePlot);
     connect(this->workerThread, &WorkerThread::threadStopped, this, &Window::threadStopped);
     this->workerThread->start();
}
