//
// Created by Biny Brion on 11/9/2018.
//

#ifndef PERFORMANCEMONITOR_SCROLLAREA_H
#define PERFORMANCEMONITOR_SCROLLAREA_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>
#include "CounterSelection.h"

// Holds all the CounterSelection classes, and displays them in a scrollable widget

// This class should be renamed honestly, but noticeable amount of code would have to be refactored
class ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit ScrollArea(QWidget *widget = nullptr);
    void setCentralWidget();
    void showWidgets(const std::vector<CounterSelection *> &widgets);

public slots:
    void setWidgets(const std::vector<CounterSelection*> &widgets);

private:

    // These widgets are needed in order to make this area scrollable- see constructor
    QWidget *scrollWidget = nullptr;
    QVBoxLayout *vBoxLayout = nullptr;
};


#endif //PERFORMANCEMONITOR_SCROLLAREA_H
