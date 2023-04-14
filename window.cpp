
#include "window.h"

#include "./ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Window) {
    ui->setupUi(this);

    this->setupChart(PayloadDataFlag::qber, ui->graphicsViewQBER, "QBER", 0, 1, 0, 1);
    this->setupChart(PayloadDataFlag::coincidenceCounts, ui->graphicsViewCoincidenceCounts, "Coincidence counts", 0, 1, 0, 1);
    this->setupChart(PayloadDataFlag::fValue, ui->graphicsViewFValue, "f value", 0, 1, 0, 2);
    this->setupChart(PayloadDataFlag::secretKeyBits, ui->graphicsViewSecretKeyBits, "secret key (bits)", 0, 1, 0, 1);

    ui->stopButton->setEnabled(false);
    setWindowTitle(tr("sQrypt GUI"));
}

Window::~Window() {
    delete ui;
}

void Window::setupChart(PayloadDataFlag payloadDataFlag, QChartView *inputChartView, QString const &title, double xMin, double xMax, double yMin, double yMax) {
    this->series[payloadDataFlag] = new QLineSeries();
    this->series[payloadDataFlag]->setUseOpenGL(true);

    this->axesX[payloadDataFlag] = new QValueAxis();
    this->axesY[payloadDataFlag] = new QValueAxis();
    this->axesX[payloadDataFlag]->setRange(xMin, xMax);
    this->axesY[payloadDataFlag]->setRange(yMin, yMax);

    this->charts[payloadDataFlag] = new QChart();

    this->charts[payloadDataFlag]->addAxis(this->axesX[payloadDataFlag], Qt::AlignBottom);
    this->charts[payloadDataFlag]->addAxis(this->axesY[payloadDataFlag], Qt::AlignLeft);

    this->charts[payloadDataFlag]->addSeries(this->series[payloadDataFlag]);

    this->series[payloadDataFlag]->attachAxis(this->axesX[payloadDataFlag]);
    this->series[payloadDataFlag]->attachAxis(this->axesY[payloadDataFlag]);

    this->charts[payloadDataFlag]->setTitle(title);

    this->charts[payloadDataFlag]->setTheme(QChart::ChartTheme::ChartThemeDark);

    inputChartView->setChart(this->charts[payloadDataFlag]);

    this->series[payloadDataFlag]->setName(title);
}

void Window::startThread() {
    this->workerThread = new WorkerThread(this);
}

void Window::updatePlot(double x, double y) {
    this->series[PayloadDataFlag::qber]->append(x, y);
    this->axesX[PayloadDataFlag::qber]->setMax(x);

    this->series[PayloadDataFlag::coincidenceCounts]->append(x, y);
    this->axesX[PayloadDataFlag::coincidenceCounts]->setMax(x);

    this->series[PayloadDataFlag::fValue]->append(x, y);
    this->axesX[PayloadDataFlag::fValue]->setMax(x);

    this->series[PayloadDataFlag::secretKeyBits]->append(x, y);
    this->axesX[PayloadDataFlag::secretKeyBits]->setMax(x);
}

void Window::threadStopped() {
    this->workerThread->wait();
    delete this->workerThread;
    this->workerThread = nullptr;
    ui->runButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
}

void Window::on_stopButton_clicked() {
    if (this->workerThread != nullptr) {
        this->workerThread->requestInterruption();
    }
}

void Window::on_runButton_clicked() {
    ui->runButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
    this->workerThread = new WorkerThread(this);
    connect(this->workerThread, &WorkerThread::updatePlot, this, &Window::updatePlot);
    connect(this->workerThread, &WorkerThread::threadStopped, this, &Window::threadStopped);
    this->workerThread->start();
}
