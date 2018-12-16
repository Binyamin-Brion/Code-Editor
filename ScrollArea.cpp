//
// Created by Biny Brion on 11/9/2018.
//

#include "ScrollArea.h"

ScrollArea::ScrollArea(QWidget *widget) : QScrollArea{widget}
{
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn );

    /*
     *  In order to make this area scrollable, a widget needs to be set as the central widget of this class (hence scrollWidget)
     *  Before this is done, the widget to be set as the central widget needs to have a layout attached (hence vBoxLayout). Layout has to be set
     *  in the soon to be central widget before it is actually set as the central widget.
     *
     *  **Note**: The scrollWidget is set as the central widget in a separate function called later from the mainwindow constructor; if this is
     *            not done, the program crashes. Unclear why this happens. Will be mentioned below as this is important.
     */

    scrollWidget = new QWidget();
    vBoxLayout = new QVBoxLayout();

    scrollWidget->setLayout(vBoxLayout);

}

// For the below functions, see the class "ScrollCommandValues(.cpp)" for what these functions do

void ScrollArea::setWidgets(const std::vector<CounterSelection *> &widgets)
{
    for(const auto &i : widgets)
    {
        vBoxLayout->addWidget(i);
    }
}

void ScrollArea::setCentralWidget()
{
   setWidget(scrollWidget);
}

void ScrollArea::showWidgets(const std::vector<CounterSelection *> &widgets)
{
    for(int i = 0; i < vBoxLayout->count(); ++i)
    {
        vBoxLayout->itemAt(i)->widget()->hide();
    }

    for(const auto &i : widgets)
    {
        i->show();
    }
}


