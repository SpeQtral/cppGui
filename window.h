
#ifndef WINDOW_H
#define WINDOW_H

#include <QChartView>
#include <QMainWindow>
#include <QtCharts>
#include <unordered_map>

#include "WorkerThread.h"
#include "payloadEnums.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow

{
    Q_OBJECT

   public:
    Window(QWidget *parent = nullptr);
    ~Window();

   private:
    Ui::Window *ui;
    WorkerThread *workerThread;
    void startThread();
    void setupChart(PayloadDataFlag payloadDataFlag, QChartView *inputChartView, QString const& title, double xMin, double xMax, double yMin, double yMax);

    std::unordered_map<PayloadDataFlag, QLineSeries *> series;
    std::unordered_map<PayloadDataFlag, QChart *> charts;
    std::unordered_map<PayloadDataFlag, QValueAxis *> axesX;
    std::unordered_map<PayloadDataFlag, QValueAxis *> axesY;

   public slots:
    void threadStopped();
    void updatePlot(double x, double y);
   private slots:
    void on_stopButton_clicked();
    void on_runButton_clicked();
};

#endif  // WINDOW_H
