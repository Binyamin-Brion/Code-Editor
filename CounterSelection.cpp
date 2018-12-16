//
// Created by Biny Brion on 11/9/2018.
//

#include "CounterSelection.h"
#include <QClipboard>

CounterSelection::CounterSelection(std::string labelText, std::string description, std::string objectName, std::string counterName, QWidget *parent) : QWidget{parent}, ui{new Ui::Form}
{
    ui->setupUi(this);

    // Show the counter name, along with the spaces so that the button to copy the counter location is not right near the counter name

    ui->label->setText(QString::fromStdString(labelText) + "          ");

    ui->label->setStyleSheet("font-style: Arial; font-size: 10pt; font-weight: bold");

    // Set an icon for the button to visually show it can be pressed in order to copy counter location

    pixmap.load("copyIcon.png");

    buttonIcon.addPixmap(pixmap);

    ui->pushButton->setIcon(buttonIcon);

    ui->pushButton->setText("");

    // Give user an informative message if they hover over the above mentioned button

    ui->pushButton->setToolTip("Copy statement to measure " + QString::fromStdString(labelText));

    // Show the included description of the counter, and format it to make it readable

    ui->label_2->setText(QString::fromStdString(description));

    ui->label_2->setWordWrap(true);

    ui->label_2->setStyleSheet("font-style: Arial; font-size: 9pt");

    // Following display the counter and object name

    ui->label_3->setText("Counter Name: " + QString::fromStdString(counterName));

    ui->label_3->setStyleSheet("font-style: Arial; font-size: 8pt");

    ui->label_4->setText("Object Name: " + QString::fromStdString(objectName));

    ui->label_4->setStyleSheet("font-style: Arial; font-size: 8pt");

    // Create the path to the counter object for use when the user requests it

    counterLocation = "\\\\" + QString::fromStdString(objectName) + "\\\\" + ui->label_3->text().split(": ")[1];

    // Copy the counter location to the clipboard if the user presses the button included in this widget

    connect(ui->pushButton, &QPushButton::clicked, [this]()
    {
        QApplication::clipboard()->setText(counterLocation);
    });
}
