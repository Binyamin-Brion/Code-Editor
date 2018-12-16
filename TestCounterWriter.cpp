//
// Created by Biny Brion on 11/2/2018.
//

#include "TestCounterWriter.h"
#include "CounterWriter.h"
#include <fstream>
#include <QtCore/QDir>
#include <processenv.h>
#include <QtTest/QtTest>
#include <pdh.h>

void TestCounterWriter::loadFiles(const std::vector<std::string> &testFilesNames, const std::vector<std::string> &resultFilesNames,
                                  std::vector<QString> &testfileContents, std::vector<QString> &resultFileContents)
{
    std::string testFilesDirectory = getTestFilesDirectory();

    for(const auto &i : testFilesNames)
    {
        testfileContents.push_back(readFile(testFilesDirectory + i));
    }

    for(const auto &i : resultFilesNames)
    {
        resultFileContents.push_back(readFile(testFilesDirectory + i));
    }
}

QString TestCounterWriter::readFile(const std::string &fileLocation)
{
    std::fstream fileReader;

    fileReader.open(fileLocation);

    if(!fileReader.is_open())
    {
        std::string functionName = " in ";
        functionName += __PRETTY_FUNCTION__;

        throw std::runtime_error{"Unable to open test file: " + fileLocation + functionName} ;
    }

    std::string fileContents;

    std::string temp;

    while(std::getline(fileReader, temp))
    {
        fileContents += temp;

        fileContents += '\n';

        temp.clear();
    }

    return QString::fromStdString(fileContents);
}

std::vector<std::string> TestCounterWriter::createExpectedFileVector(const std::vector<std::string> &codeFiles)
{
    std::vector<std::string> files;

    for(const auto &i : codeFiles)
    {
        files.push_back(i.substr(0, i.find_last_of("\\.")) + "Expected.cpp");

        printf("%s \n", files.back().c_str());
    }

    return files;
}

void TestCounterWriter::writeCounters(const std::vector<std::string> &testFileNames, std::vector<QString> &fileContents, const std::vector<std::vector<int>> &measurePoints)
{
    std::vector<FileInformation> files;

    QCOMPARE(testFileNames.size(), fileContents.size());

    for(int i = 0; i < testFileNames.size(); ++i)
    {
        files.push_back(FileInformation{QString::fromStdString(testFileNames[i]), fileContents[i], measurePoints[i]});

        //printf("Name: %s \n Content: %s \n Measure Points siz: %d \n\n\n", testFileNames[i].c_str(), fileContents[i].toStdString().c_str(), measurePoints[i].size());
    }

    CounterWriter counterWriter;

    counterWriter.writeMeasureCounters(files, "/TestFiles");
}

void TestCounterWriter::deletedFiles()
{
    QDir currentDirectory{QString::fromStdString(getTestFilesDirectory())};

    foreach(QString dirFile, currentDirectory.entryList())
        {
            currentDirectory.remove(dirFile);
        }
}

std::string TestCounterWriter::getTestFilesDirectory()
{
    std::string testFilesDirectory;

#ifdef WIN32

    char buffer[1024];

    GetCurrentDirectory(1024, buffer);

    testFilesDirectory += buffer;

   // testFilesDirectory = testFilesDirectory.substr(0, testFilesDirectory.find_last_of("\\+"));

#elif linux
    #error "Linux not supported yet!"
#endif

    testFilesDirectory += "/TestFiles/";

    return testFilesDirectory;
}

std::vector<int> TestCounterWriter::findMeasurePoints(const QString &text, const QString &fileName)
{
    QString ofstreamName{"std::ofstream "};
    ofstreamName += fileName;
    ofstreamName.remove('.');
    ofstreamName += ";\n";

    ofstreamName.remove('.');

    std::vector<int> measurePoints;

    QRegularExpression regExp{ofstreamName};

    QRegularExpressionMatchIterator matchIterator = regExp.globalMatch(text);

    QRegularExpressionMatch previousMatch;

    int counter = 0;

    while(matchIterator.hasNext())
    {
        QRegularExpressionMatch match = matchIterator.next();

        if(counter > 0)
        {
            measurePoints.push_back(match.capturedStart() - previousMatch.capturedLength());

            printf("Last pint: %d \n", previousMatch.capturedLength());
        }
        else
        {
            measurePoints.push_back(match.capturedStart());
        }

        previousMatch = match;

        ++counter;
    }

    regExp.setPattern("INSERT HERE");

    matchIterator = regExp.globalMatch(text);

    while(matchIterator.hasNext())
    {
        QRegularExpressionMatch match = matchIterator.next();

        measurePoints.push_back(match.capturedStart() - previousMatch.capturedLength());

        previousMatch = match;

        printf("Last pint: %d \n", previousMatch.capturedLength());
    }

    std::sort(measurePoints.begin(), measurePoints.end());

    return measurePoints;
}

static TestCounterWriter TEST_COUNTERWRITER;
