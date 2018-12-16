//
// Created by Biny Brion on 10/27/2018.
//

#include "CounterWriter.h"
#include <fstream>
#include <processenv.h>

CounterWriter::CounterWriter() : regularExpression{"//\\s*@Measure"}, functionStart{"[A-Z][a-z]"}
{

}

void CounterWriter::writeMeasureCounters(std::vector<FileInformation> &files, std::string saveDestination)
{
    std::string workingDirectory;

#ifdef WIN32

    char buffer[1024];

    GetCurrentDirectory(1024, buffer);

    workingDirectory += buffer;

#elif linux
    #error "Linux not supported!"
#endif

    workingDirectory += saveDestination;
    workingDirectory += '/';



    for(const auto &i : files)
    {
        printf("%s, %s, %d \n", i.fileName.toStdString().c_str(), i.fileContent.toStdString().c_str(), i.measurePoints.size());
    }

    for(auto &f : files)
    {
        std::ofstream fileWriter;

        fileWriter.open(workingDirectory + f.fileName.toStdString());

        if(!fileWriter.is_open())
        {
            assert(false);
        }

       // printf("REading: %s \n", (workingDirectory + f.fileName.toStdString()).c_str());

        QRegularExpressionMatchIterator matchIterator = regularExpression.globalMatch(f.fileContent);

        std::vector<int> matches;

        while(matchIterator.hasNext())
        {
            auto x = matchIterator.next();

            matches.push_back(x.capturedStart() + x.capturedLength());
        }

        bool newFileWriter = false;

       // printf("Matches size: %d \n", matches.size());

        for(int i = 0; i < matches.size(); ++i)
        {
            QString toInsert = "std::ofstream ";
            toInsert += f.fileName;
            toInsert.remove('.');
            toInsert += "; \n";

            newFileWriter = true;

            for(int j = 0; j < f.measurePoints.size(); ++j)
            {

                printf("Point: %d \n", f.measurePoints[j]);

                if(i != matches.size() - 1)
                {
                    if(f.measurePoints[j] > matches[i + 1])
                    {
                        break;
                    }
                }

                if(f.measurePoints[j] < matches[i])
                {
                    continue;
                }

                if(newFileWriter)
                {
                    f.fileContent.insert(f.measurePoints[j], toInsert);

                    for(int k = i; k < matches.size(); ++k)
                    {
                        matches[k] += toInsert.size();
                    }

                    for(int k = j; k < f.measurePoints.size(); ++k)
                    {
                        f.measurePoints[k] += toInsert.size();
                    }

                    newFileWriter = false;
                }

                std::string anotherInsert{"INSERT HERE "};

                f.fileContent.insert(f.measurePoints[j], QString::fromStdString(anotherInsert));

                for(int k = i; k < matches.size(); ++k)
                {
                    matches[k] += anotherInsert.size();
                }

                for(int k = j; k < f.measurePoints.size(); ++k)
                {
                    f.measurePoints[k] += anotherInsert.size();
                }

             //   printf("\n Content is now: %s \n", f.fileContent.toStdString().c_str());
            }
        }

        fileWriter << f.fileContent.toStdString();
    }
}
