//
// Created by Biny Brion on 10/27/2018.
//

#ifndef PERFORMANCEMONITOR_COUNTERWRITER_H
#define PERFORMANCEMONITOR_COUNTERWRITER_H


#include <QtCore/QRegularExpression>

struct FileInformation
{
    QString fileName;
    QString fileContent;
    std::vector<int> measurePoints;
};

class CounterWriter
{
    friend class TestCounterWriter;

public:

    CounterWriter();
    void writeMeasureCounters(std::vector<FileInformation> &files, std::string saveDestination);

private:

    std::vector<QString> files;
    QRegularExpression regularExpression;
    QRegularExpression functionStart;
};


#endif //PERFORMANCEMONITOR_COUNTERWRITER_H
