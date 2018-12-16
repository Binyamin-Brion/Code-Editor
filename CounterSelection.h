//
// Created by Biny Brion on 11/9/2018.
//

#ifndef PERFORMANCEMONITOR_COUNTERSELECTION_H
#define PERFORMANCEMONITOR_COUNTERSELECTION_H

#include <QtWidgets/QWidget>
#include "ui_CounterSelection.h"

//  Holds information regarding each counter, and displays them in a scrollable list

class CounterSelection : public QWidget
{
public:

    explicit CounterSelection(std::string labelText, std::string description, std::string objectName, std::string counterName, QWidget *parent = nullptr);

private:

    Ui::Form *ui = nullptr;

    // Pixmap and Icon work together in order to display an image on a widget (in this case a push button to copy the counter location)

    QPixmap pixmap;
    QIcon buttonIcon;

    QString counterLocation;
};


#endif //PERFORMANCEMONITOR_COUNTERSELECTION_H
