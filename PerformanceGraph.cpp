//
// Created by Biny Brion on 11/22/2018.
//

#include "PerformanceGraph.h"
#include <fstream>

PerformanceGraph::PerformanceGraph(QWidget *parent) : QWidget{parent}
{
    chart = new QChart;
    lineChart = new QLineSeries;
}

void PerformanceGraph::setGraphType()
{
    std::fstream valueReader;

    valueReader.open("values.txt");

    if(!valueReader.is_open())
    {
        printf("Could not find file! \n");

        return;
    }

    std::string currentLine;

    std::vector<float> xValues;

    std::vector<float> yValues;

    while(std::getline(valueReader, currentLine))
    {
        QString qCurrentLine = QString::fromStdString(currentLine);

        auto values = qCurrentLine.split(",");

        xValues.push_back(values[0].toFloat());

        yValues.push_back(values[1].toFloat());
    }


}
