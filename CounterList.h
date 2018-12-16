//
// Created by Biny Brion on 11/8/2018.
//

#ifndef PERFORMANCEMONITOR_COUNTERLIST_H
#define PERFORMANCEMONITOR_COUNTERLIST_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <unordered_map>
#include "ScrollArea.h"

// Class to hold the list of available performance counters grouped by what the counters measure- shown as a drop down menu.
// This class also contains a scroll area to hold the list of counters

class CounterList : public QComboBox
{
    Q_OBJECT

public:

    explicit CounterList(QWidget *parent = nullptr);
    void loadCounters();
    void setScrollAreaPtr(ScrollArea *area);

private slots:
    // Function to forward vector of CounterSelection to show in the appropriate scroll area- see constructor definition for why
    void changeScrollAreaContents(QString itemName);

private:

    // Hold the object types, and a list of associated CounterSelection to hold associated counters
    std::unordered_map<std::string, std::vector<CounterSelection*>> counters;

    // Hold pointer to instance of a scrollable area holding selected counter for an object type. See constructor definition for why
    ScrollArea *counterScrollArea = nullptr;

};


#endif //PERFORMANCEMONITOR_COUNTERLIST_H
