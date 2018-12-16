//
// Created by Biny Brion on 11/2/2018.
//

#ifndef PERFORMANCEMONITOR_TESTCOUNTERWRITER_H
#define PERFORMANCEMONITOR_TESTCOUNTERWRITER_H


#include "TestSuite.h"

class TestCounterWriter : public TestSuite
{
    Q_OBJECT

private slots:

    //void testOneMeasure();

private:

    std::vector<std::string> createExpectedFileVector(const std::vector<std::string> &codeFiles);

    void deletedFiles();

    std::vector<int> findMeasurePoints(const QString &text, const QString &fileName);

    std::string getTestFilesDirectory();

    void loadFiles(const std::vector<std::string> &testFilesNames, const std::vector<std::string> &resultFilesNames,
                   std::vector<QString> &testfileContents, std::vector<QString> &resultFileContents);

    QString readFile(const std::string &fileLocation);

    void writeCounters(const std::vector<std::string> &testFileNames, std::vector<QString> &fileContents, const std::vector<std::vector<int>> &measurePoints);

};


#endif //PERFORMANCEMONITOR_TESTCOUNTERWRITER_H
