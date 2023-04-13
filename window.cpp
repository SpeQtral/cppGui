
#include "window.h"
#include "./ui_window.h"
#include <QtCharts>
#include <QChartView>
#include <cmath>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    QScatterSeries *series = new QScatterSeries();
    series->setUseOpenGL(true);
    for (int i =0;i<100;i++){
        *series << QPointF(i,std::sin(i*0.1));
    }


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Testing chart");
    chart->createDefaultAxes();
    chart->setTheme(QChart::ChartTheme::ChartThemeDark);
    ui->graphicsView->setChart(chart);

}

Window::~Window()
{
    delete ui;
}


