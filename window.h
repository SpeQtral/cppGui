
#ifndef WINDOW_H
#define WINDOW_H

#include <QChartView>
#include <QMainWindow>
#include <QtCharts>

#include "WorkerThread.h"

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
//    Controller *controller;
    void startThread();
    QScatterSeries *series;
    QChart *chart;
    QValueAxis *axisX;
    QValueAxis *axisY;

   public slots:
    void threadStopped();
    void updatePlot(double x, double y);
   private slots:
    void on_stopButton_clicked();
    void on_runButton_clicked();
};

#endif  // WINDOW_H
