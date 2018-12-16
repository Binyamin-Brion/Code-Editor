//
// Created by Biny Brion on 11/16/2018.
//

#include "ScrollCommandValues.h"

ScrollCommandValues::ScrollCommandValues(QWidget *parent) : QScrollArea{parent}
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

void ScrollCommandValues::setCentralWidget()
{
    // Set the central widget as that of the scroll widget- reason for having a separate function discussed above in the constructor
    setWidget(scrollWidget);
}

void ScrollCommandValues::setItems(const std::vector<QPushButton*> &labels)
{
    // For every PDH command, add its list of push-buttons showing the command's associated values to this widget (done once)
    // By doing this, the values can be shown simply by calling show() or hide() on the required buttons

    for(const auto &i : labels)
    {
        // Default set the push-buttons as hidden
        i->hide();

        // Add the the push-buttons to the layout to be displayed by this scrollable widget (default they are hidden)
        vBoxLayout->addWidget(i);
    }
}

void ScrollCommandValues::showItems(const std::vector<QPushButton *> &labels)
{
    // Make the selected push-buttons associated with the (checked in DisplayCommand) PDH command visible

    for(const auto &i : labels)
    {
        i->show();
    }
}

void ScrollCommandValues::hideItems(const std::vector<QPushButton *> &labels)
{
    // Make the selected push-buttons associated with the (unchecked in DisplayCommand) PDH command invisible

    for(const auto &i : labels)
    {
        i->hide();
    }
}
