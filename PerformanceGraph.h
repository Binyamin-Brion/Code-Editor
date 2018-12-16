//
// Created by Biny Brion on 11/22/2018.
//

#ifndef PERFORMANCEMONITOR_PERFORMANCEGRAPH_H
#define PERFORMANCEMONITOR_PERFORMANCEGRAPH_H


#include <QtWidgets/QWidget>
#include <QtCharts>

class PerformanceGraph : public QWidget
{
    Q_OBJECT

public:
    explicit PerformanceGraph(QWidget *parent = nullptr);

public slots:
    void setGraphType();


private:

    QChart *chart = nullptr;
    QLineSeries *lineChart = nullptr;
};


#endif //PERFORMANCEMONITOR_PERFORMANCEGRAPH_H
