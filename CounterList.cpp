//
// Created by Biny Brion on 11/8/2018.
//


#include "CounterList.h"
#include <fstream>

CounterList::CounterList(QWidget *parent)
{
    // When a different type of performance counter is selected (such as "memory"), change the list of performance
    // counters shown in the scroll area to those that measure memory characteristics
    connect(this, SIGNAL(activated(QString)), this, SLOT(changeScrollAreaContents(QString)));

    // Note: connect with lambda syntax not used as this gives errors for some reason
}

void CounterList::loadCounters()
{
    // Open the file containing the list of performance counters (among other counter information)

    std::fstream countersReader{"counters.txt"};

    if(!countersReader.is_open())
    {
        printf("Unable to load the counter list! \n");

        return;
    }

    // Hold the current read line from the file
    std::string currentLine;

    // Hold what type of object the counter is (ie Memory, Processor, etc)
    std::string object;

    // Hold the counter name (ie User Time, Processor Time, etc)
    std::string counter;

    // Hold the description of what the counter measures
    std::string counterDescription;

    // Hold the object name to be used when specifying the counter location (ie Processor(*))
    std::string objectName;

    // Hold the counter name when specifying the counter name (ie % Priviliged Time)
    std::string counterName;

    // Variables to hold information about what has been read and what will be read
    bool readingObjectType = false;
    bool readingCounter = false;
    bool readingCounterDescription = false;
    bool readingObjectName = false;
    bool readingCounterName = false;

    while(std::getline(countersReader, currentLine))
    {
        if(readingObjectType)
        {
            object = currentLine;

            // Create a std::pair to hold the name of the object type and associated counters

            std::pair<std::string, std::vector<CounterSelection*>> pair{object, std::vector<CounterSelection*>{}};

            // Add pair to hashmap so that CounterSelections can be added later by specifying the object type

            counters.insert(pair);

            readingObjectType = false;
        }

        // readingXXX variables set to false to prevent overwriting the correct value in the next iteration of the loop

        if(readingCounter)
        {
            // Copy the name of the counter for use later
            counter = currentLine;

            readingCounter = false;
        }

        if(readingCounterDescription)
        {
            // Copy the name of the counter description for use later
            counterDescription = currentLine;

            readingCounterDescription = false;
        }

        if(readingObjectName)
        {
            // Copy the name of the objectName (for use in counter location path) for use later
            objectName = currentLine;

            readingObjectName = false;
        }

        if(readingCounterName)
        {
            // Copy the name of the counter name (for use in counter location path) for use later
            counterName = currentLine;

            // Attempt to add a new CounterSelection using the read information
            try
            {
                counters.at(object).push_back(new CounterSelection{counter, counterDescription, objectName, counterName});

                // setWidgets logic described in ScrollCommandValues class
                counterScrollArea->setWidgets(counters.at(object));

            }
            catch(std::out_of_range &e)
            {
                printf("Error reading format file- could not locate object in hashmap! \n : %s ", e.what());

                return;
            }

            readingCounterName = false;
        }

        // If the current read line of the file matches the appropriate headers specifying what location is on the next line,
        // set the appropriate readingXXX variable so that information on the next line is stored in memory

        if("OBJECT" == currentLine)
        {
            readingObjectType = true;
        }

        if("COUNTER" == currentLine)
        {
            readingCounter = true;
        }

        if("DESCRIPTION" == currentLine)
        {
            readingCounterDescription = true;
        }

        if("OBJECT NAME" == currentLine)
        {
            readingObjectName = true;
        }

        if("COUNTER NAME" == currentLine)
        {
            readingCounterName = true;
        }
    }

    // Iterate over hahsmap and add all object types to the drop-down list showing available object types

    for(const auto &i : counters)
    {
        addItem(QString::fromStdString(i.first));
    }

    counterScrollArea->showWidgets(counters[object]);
}

void CounterList::setScrollAreaPtr(ScrollArea *area)
{
    // Set the scrrollArea pointer in this class to point to the appropriate instance- see constructor for why

    counterScrollArea = area;
}

void CounterList::changeScrollAreaContents(QString itemName)
{
    // Change the counters shown when a different object type is selected in the drop-down list

    counterScrollArea->showWidgets(counters[itemName.toStdString()]);
}