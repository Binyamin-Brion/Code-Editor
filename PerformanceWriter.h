//
// Created by Biny Brion on 10/27/2018.
//

#ifndef PERFORMANCEMONITOR_PERFORMANCEWRITER_H
#define PERFORMANCEMONITOR_PERFORMANCEWRITER_H


#include <QtCore/QObject>
#include <QtCore/QRegularExpression>

class PerformanceWriter
{

public:

    PerformanceWriter();

private:

    QRegularExpression regularExpression;

};


#endif //PERFORMANCEMONITOR_PERFORMANCEWRITER_H
